.intel_syntax noprefix
.text
.global _start
_start:
xor eax, eax
inc eax
mov ebx, eax
shl eax, 2

lea ecx, [.L_hello]
mov edx, .L_hello_end - .L_hello
int 0x80
xor eax, eax
mov ebx, eax
inc eax
int 0x80
.data
.L_hello:
.ascii "Hello, World!"
.L_hello_end:
ret
