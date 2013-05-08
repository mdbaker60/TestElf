	.file	"iotest.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"\012\015\000"
	.text
	.align	2
	.global	nl
	.type	nl, %function
nl:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {sl, fp, ip, lr, pc}
	sub	fp, ip, #4
	ldr	sl, .L4
.L3:
	add	sl, pc, sl
	mov	r0, #1
	ldr	r3, .L4+4
	add	r3, sl, r3
	mov	r1, r3
	bl	bwputstr(PLT)
	ldmfd	sp, {sl, fp, sp, pc}
.L5:
	.align	2
.L4:
	.word	_GLOBAL_OFFSET_TABLE_-(.L3+8)
	.word	.LC0(GOTOFF)
	.size	nl, .-nl
	.section	.rodata
	.align	2
.LC2:
	.ascii	"argument\012\015\000"
	.align	2
.LC1:
	.ascii	"str[]\012\015\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 20
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {sl, fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #20
	ldr	sl, .L9
.L8:
	add	sl, pc, sl
	str	r0, [fp, #-32]
	str	r1, [fp, #-36]
	ldr	r3, .L9+4
	add	r3, sl, r3
	sub	r2, fp, #25
	mov	ip, #8
	mov	r0, r2
	mov	r1, r3
	mov	r2, ip
	bl	memcpy(PLT)
	mov	r3, #99
	strb	r3, [fp, #-17]
	mov	r0, #1
	mov	r1, #0
	bl	bwsetfifo(PLT)
	sub	r3, fp, #25
	mov	r0, #1
	mov	r1, r3
	bl	bwputstr(PLT)
	mov	r0, #1
	ldr	r3, .L9+8
	add	r3, sl, r3
	mov	r1, r3
	bl	bwputstr(PLT)
	bl	nl(PLT)
	mov	r0, #1
	mov	r1, #99
	bl	bwputc(PLT)
	mov	r0, #1
	mov	r1, #99
	bl	bwputx(PLT)
	mov	r0, #1
	mov	r1, #0
	bl	bwputr(PLT)
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #16
	ldmfd	sp, {sl, fp, sp, pc}
.L10:
	.align	2
.L9:
	.word	_GLOBAL_OFFSET_TABLE_-(.L8+8)
	.word	.LC1(GOTOFF)
	.word	.LC2(GOTOFF)
	.size	main, .-main
	.ident	"GCC: (GNU) 4.0.2"
