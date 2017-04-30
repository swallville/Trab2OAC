.data
x: .word 0x000fffff
y: .word 0x0f0f0f00

.text
	la $t0,x
	la $t1,y
	lw $t0,0($t0)
	li $t2, 20568714
	ori $t3,$t2,0xf0f0f0f0
	lw $t1,0($t1)
	mult $t0,$t1
	div $t0,$t1
