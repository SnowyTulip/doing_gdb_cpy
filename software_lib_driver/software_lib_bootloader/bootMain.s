.section .qxinit
.global main

movigh GR30 0x0003||
movigl GR30 0x0000||
call main||
nop||
nop||
nop||
movigh GR0 0x0000||
movigl GR0 0x0400||
callr GR0||
nop||
nop||
nop||
.section .qxexit
myloop:
nop|nop|nop
jmp myloop||
nop|nop|nop
nop|nop|nop
