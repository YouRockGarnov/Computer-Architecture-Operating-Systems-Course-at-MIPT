
.text

.global calculate
calculate:
	LDRB r1, [r0]
	LDRH r2, [r0, #2]
	LDR r3, [r0, #4]

	ADD r0, r1, r2
	ADDS r3, r0, r3

	MOV r2, #0
	ADC r2, #0

	MOV r1, r2
	MOV r0, r3
	BX lr

//more beautiful
