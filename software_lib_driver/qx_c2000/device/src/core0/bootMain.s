.section .qxbootinit
.global bootmain

movigh GR30 0x0003||
movigl GR30 0x0000||
call bootmain||
nop||
nop||
nop||
movigh GR0 0x0020||
movigl GR0 0x0400||
callr GR0||
nop||
nop||

mybootloop:
nop|nop|nop
jmp mybootloop||
nop|nop|nop
nop|nop|nop

