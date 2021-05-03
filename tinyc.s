.text

.globl main

main:
	pushq %rbp
	movq %rsp, %rbp
	mov $5, %eax
	push %eax
	mov $5, %eax
	push %eax
	mov $1, %eax
	mov %eax, %ecx
	pop %eax
	mov %edx, 0
	div %ecx
	push %eax
	mov $2, %eax
	pop %ebx
	add %ebx, %eax
	popq %rbp
	ret
