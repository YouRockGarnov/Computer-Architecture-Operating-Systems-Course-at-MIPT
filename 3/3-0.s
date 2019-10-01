.text
.global f

f:
	mul r1, r3, r1
	add r1, r2, r1
	mul r2, r3, r3
	mul r2, r0, r2
	add r1, r1, r2
	mov r0, r1
	bx lr
