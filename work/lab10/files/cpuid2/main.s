	.file	"main.c"
	.text
	.type	decode_vendor_string, @function
decode_vendor_string:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movq	%rcx, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	-4(%rbp), %edx
	movl	%edx, (%rax)
	movq	-24(%rbp), %rax
	leaq	4(%rax), %rdx
	movl	-12(%rbp), %eax
	movl	%eax, (%rdx)
	movq	-24(%rbp), %rax
	leaq	8(%rax), %rdx
	movl	-8(%rbp), %eax
	movl	%eax, (%rdx)
	movq	-24(%rbp), %rax
	addq	$12, %rax
	movb	$0, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	decode_vendor_string, .-decode_vendor_string
	.section	.rodata
.LC0:
	.string	"usage: %s CPUID_OP\n"
	.align 8
.LC1:
	.string	"cpuid(%d): eax = 0x%x; ebx = 0x%x; edx = 0x%x; ecx = 0x%x\n"
.LC2:
	.string	"vendor: %s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	cmpl	$2, -52(%rbp)
	je	.L3
	movq	-64(%rbp), %rax
	movq	(%rax), %rdx
	movq	stderr(%rip), %rax
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$1, %edi
	call	exit@PLT
.L3:
	movq	-64(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -4(%rbp)
	leaq	-20(%rbp), %rdi
	leaq	-16(%rbp), %rcx
	leaq	-12(%rbp), %rdx
	leaq	-8(%rbp), %rsi
	movl	-4(%rbp), %eax
	movq	%rdi, %r8
	movl	%eax, %edi
	call	get_cpuid@PLT
	movl	-16(%rbp), %edi
	movl	-20(%rbp), %esi
	movl	-12(%rbp), %ecx
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edi, %r9d
	movl	%esi, %r8d
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpl	$0, -4(%rbp)
	jne	.L4
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %esi
	movl	-12(%rbp), %eax
	leaq	-33(%rbp), %rcx
	movl	%eax, %edi
	call	decode_vendor_string
	leaq	-33(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L4:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
