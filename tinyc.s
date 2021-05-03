.text

.globl main

main:
	pushq %rbp
	movq %rsp, %rbp
	mov $8, %eax
	push %eax
	mov $1, %eax
	push %eax
	mov $2, %eax
	pop %ebx
	sub %ebx, %eax
	pop %ebx
	add %ebx, %eax
	popq %rbp
	ret
