.text
.global classify

classify:
			PUSH {r5, r6, r7, r8}

			MOV		r7, #0x7F000000
			ORR		r7, r7, #0x00F00000
			MOV		r8, #0x000FF000
			ORR		r8, r8, #0x00000FF0
			ORR		r8, r8, #0x0000000F

			LDR 		r2, [r0]
			LDR 		r1, [r0, #4]

			AND		r3, r1, #0x80000000
			AND		r4, r1, r7
			AND		r5, r1, r8
			AND		r6, r1, #0x00080000
			CMP		r4, #0
			BEQ		zExp
			CMP		r4, r7
			BEQ		exp
			CMP		r3, #0
			BEQ		plusR
			MOV		r0, #0x11
			B end

plusR:
			MOV		r0, #0x10
			B end

zExp:
			CMP		r2, #0
			Bne		denormal
			CMP		r5, #0
			Bne		denormal
			CMP		r3, #0
			BEQ		plusZero
			MOV		r0, #0x01
			B end

plusZero:
			MOV		r0, #0x00
			B end

denormal:
			CMP		r3, #0
			BEQ		plusDenormal
			MOV		r0, #0x21
			B end

plusDenormal:
			MOV		r0, #0x20
			B end

exp:
			CMP		r2, #0
			Bne		NaN
			CMP		r5, #0
			Bne		NaN
			CMP		r3, #0
			BEQ		plusInf
			MOV		r0, #0xF1
			B end

plusInf:
			MOV		r0, #0xF0
			B end

NaN:
			CMP		r6, #0
			BEQ		sNaN
			MOV		r0, #0x31
			B end

sNaN:
			MOV		r0, #0x30
			B end

end:
	pop {r5,r6,r7,r8}
	BX lr
