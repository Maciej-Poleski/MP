	.file	"satori.cxx"
	.text
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6resizeEm, @function
_ZN12_GLOBAL__N_110MinMaxHeapIjjE6resizeEm:
.LFB1544:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	leaq	0(,%rsi,8), %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	movq	%r12, %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	_Znam
	movq	16(%rbx), %rcx
	movq	%rax, %r13
	xorl	%eax, %eax
	movq	(%rbx), %rdi
	testq	%rcx, %rcx
	je	.L3
	.p2align 4,,10
	.p2align 3
.L4:
	movq	(%rdi,%rax,8), %rdx
	movq	%rdx, 0(%r13,%rax,8)
	addq	$1, %rax
	cmpq	%rcx, %rax
	jne	.L4
.L3:
	testq	%rdi, %rdi
	je	.L5
	call	_ZdaPv
.L5:
	movq	%r12, %rdi
	movq	%r13, (%rbx)
	call	_Znam
	movq	16(%rbx), %rcx
	movq	%rax, %r12
	xorl	%eax, %eax
	movq	8(%rbx), %rdi
	testq	%rcx, %rcx
	je	.L7
	.p2align 4,,10
	.p2align 3
.L8:
	movq	(%rdi,%rax,8), %rdx
	movq	%rdx, (%r12,%rax,8)
	addq	$1, %rax
	cmpq	%rcx, %rax
	jne	.L8
.L7:
	testq	%rdi, %rdi
	je	.L9
	call	_ZdaPv
.L9:
	movq	%r12, 8(%rbx)
	movq	%rbp, 24(%rbx)
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1544:
	.size	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6resizeEm, .-_ZN12_GLOBAL__N_110MinMaxHeapIjjE6resizeEm
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMinEm.part.7, @function
_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMinEm.part.7:
.LFB1570:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	16(%rdi), %r11
	movq	(%rdi), %r8
	movq	8(%rdi), %r12
	movq	%r11, %rbx
	leaq	(%r8,%rsi,8), %rdx
	shrq	%rbx
	cmpq	%rbx, %rsi
	movl	(%rdx), %r10d
	movl	4(%rdx), %ebp
	jb	.L19
	jmp	.L23
	.p2align 4,,10
	.p2align 3
.L25:
	leaq	(%r8,%rcx,8), %r13
	movl	(%rdx), %r9d
	movl	0(%r13), %edi
	cmpl	%r9d, %edi
	jae	.L21
	movq	%r13, %rdx
	movq	%rcx, %rax
.L20:
	cmpl	%edi, %r10d
	jb	.L24
.L18:
	movq	(%rdx), %rcx
	movq	%rcx, (%r8,%rsi,8)
	shrq	$32, %rcx
	cmpq	%rbx, %rax
	movl	%esi, 4(%r12,%rcx,8)
	jae	.L15
	movq	%rax, %rsi
.L19:
	leaq	(%rsi,%rsi), %rdx
	leaq	2(%rdx), %rcx
	leaq	1(%rdx), %rax
	cmpq	%r11, %rcx
	leaq	(%r8,%rax,8), %rdx
	jb	.L25
	movl	(%rdx), %edi
	cmpl	%edi, %r10d
	jae	.L18
.L24:
	leaq	(%r8,%rsi,8), %rdx
.L23:
	movq	%rsi, %rax
.L15:
	movl	%r10d, (%rdx)
	movl	%ebp, 4(%rdx)
	movl	%eax, 4(%r12,%rbp,8)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L21:
	.cfi_restore_state
	movl	%r9d, %edi
	jmp	.L20
	.cfi_endproc
.LFE1570:
	.size	_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMinEm.part.7, .-_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMinEm.part.7
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMaxEm.part.9, @function
_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMaxEm.part.9:
.LFB1572:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	16(%rdi), %r11
	movq	8(%rdi), %r8
	movq	(%rdi), %r12
	movq	%r11, %rbx
	leaq	(%r8,%rsi,8), %rdx
	shrq	%rbx
	cmpq	%rbx, %rsi
	movl	(%rdx), %r10d
	movl	4(%rdx), %ebp
	jb	.L32
	jmp	.L35
	.p2align 4,,10
	.p2align 3
.L37:
	leaq	(%r8,%rcx,8), %r9
	movl	(%rdx), %edi
	movl	(%r9), %r13d
	cmpl	%r13d, %edi
	jae	.L33
	movl	%r13d, %edi
	movq	%r9, %rdx
	movq	%rcx, %rax
.L33:
	cmpl	%edi, %r10d
	ja	.L36
.L31:
	movq	(%rdx), %rcx
	movq	%rcx, (%r8,%rsi,8)
	shrq	$32, %rcx
	cmpq	%rbx, %rax
	movl	%esi, 4(%r12,%rcx,8)
	jae	.L28
	movq	%rax, %rsi
.L32:
	leaq	(%rsi,%rsi), %rdx
	leaq	2(%rdx), %rcx
	leaq	1(%rdx), %rax
	cmpq	%r11, %rcx
	leaq	(%r8,%rax,8), %rdx
	jb	.L37
	movl	(%rdx), %edi
	cmpl	%edi, %r10d
	jbe	.L31
.L36:
	leaq	(%r8,%rsi,8), %rdx
.L35:
	movq	%rsi, %rax
.L28:
	movl	%r10d, (%rdx)
	movl	%ebp, 4(%rdx)
	movl	%eax, 4(%r12,%rbp,8)
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1572:
	.size	_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMaxEm.part.9, .-_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMaxEm.part.9
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_110MinMaxHeapIjjED2Ev.isra.10, @function
_ZN12_GLOBAL__N_110MinMaxHeapIjjED2Ev.isra.10:
.LFB1573:
	.cfi_startproc
	testq	%rdi, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rsi, %rbx
	je	.L39
	call	_ZdaPv
.L39:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L38
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	_ZdaPv
	.p2align 4,,10
	.p2align 3
.L38:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1573:
	.size	_ZN12_GLOBAL__N_110MinMaxHeapIjjED2Ev.isra.10, .-_ZN12_GLOBAL__N_110MinMaxHeapIjjED2Ev.isra.10
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMinEv.constprop.13, @function
_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMinEv.constprop.13:
.LFB1576:
	.cfi_startproc
	movq	%rbx, -24(%rsp)
	movq	%rbp, -16(%rsp)
	xorl	%ecx, %ecx
	movq	%r12, -8(%rsp)
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -16
	.cfi_offset 6, -24
	.cfi_offset 3, -32
	movq	16(%rdi), %rax
	movq	(%rdi), %rdx
	movq	%rdi, %rbx
	subq	$1, %rax
	testq	%rax, %rax
	movl	(%rdx), %ebp
	movl	4(%rdx), %r12d
	movq	%rax, 16(%rdi)
	je	.L42
	movq	(%rdx,%rax,8), %rcx
	movq	%rcx, (%rdx)
	movq	8(%rdi), %rdx
	shrq	$32, %rcx
	cmpq	$1, %rax
	movl	$0, 4(%rdx,%rcx,8)
	movl	$1, %ecx
	je	.L43
	xorl	%esi, %esi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMinEm.part.7
	movq	16(%rbx), %rcx
.L43:
	movl	%r12d, %esi
	cmpq	%rcx, %rsi
	jb	.L47
.L42:
	movq	24(%rbx), %rsi
	salq	$2, %rcx
	cmpq	%rsi, %rcx
	jae	.L44
	shrq	%rsi
	movq	%rbx, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6resizeEm
.L44:
	movl	%ebp, %eax
	movq	(%rsp), %rbx
	movq	8(%rsp), %rbp
	movq	16(%rsp), %r12
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L47:
	.cfi_restore_state
	movq	8(%rbx), %rdx
	movq	(%rdx,%rcx,8), %rax
	movq	%rax, (%rdx,%rsi,8)
	movq	(%rbx), %rdx
	shrq	$32, %rax
	movl	%r12d, 4(%rdx,%rax,8)
	movq	%rcx, %rax
	shrq	%rax
	cmpq	%rax, %rsi
	jae	.L42
	movq	%rbx, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMaxEm.part.9
	movq	16(%rbx), %rcx
	jmp	.L42
	.cfi_endproc
.LFE1576:
	.size	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMinEv.constprop.13, .-_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMinEv.constprop.13
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMaxEv.constprop.14, @function
_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMaxEv.constprop.14:
.LFB1575:
	.cfi_startproc
	movq	%rbx, -24(%rsp)
	movq	%rbp, -16(%rsp)
	xorl	%ecx, %ecx
	movq	%r12, -8(%rsp)
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -16
	.cfi_offset 6, -24
	.cfi_offset 3, -32
	movq	16(%rdi), %rax
	movq	8(%rdi), %rdx
	movq	%rdi, %rbx
	subq	$1, %rax
	testq	%rax, %rax
	movl	(%rdx), %ebp
	movl	4(%rdx), %r12d
	movq	%rax, 16(%rdi)
	je	.L49
	movq	(%rdx,%rax,8), %rcx
	movq	%rcx, (%rdx)
	movq	(%rdi), %rdx
	shrq	$32, %rcx
	cmpq	$1, %rax
	movl	$0, 4(%rdx,%rcx,8)
	movl	$1, %ecx
	je	.L50
	xorl	%esi, %esi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMaxEm.part.9
	movq	16(%rbx), %rcx
.L50:
	movl	%r12d, %esi
	cmpq	%rcx, %rsi
	jb	.L54
.L49:
	movq	24(%rbx), %rsi
	salq	$2, %rcx
	cmpq	%rsi, %rcx
	jae	.L51
	shrq	%rsi
	movq	%rbx, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6resizeEm
.L51:
	movl	%ebp, %eax
	movq	(%rsp), %rbx
	movq	8(%rsp), %rbp
	movq	16(%rsp), %r12
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L54:
	.cfi_restore_state
	movq	(%rbx), %rdx
	movq	(%rdx,%rcx,8), %rax
	movq	%rax, (%rdx,%rsi,8)
	movq	8(%rbx), %rdx
	shrq	$32, %rax
	movl	%r12d, 4(%rdx,%rax,8)
	movq	%rcx, %rax
	shrq	%rax
	cmpq	%rax, %rsi
	jae	.L49
	movq	%rbx, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE11downheapMinEm.part.7
	movq	16(%rbx), %rcx
	jmp	.L49
	.cfi_endproc
.LFE1575:
	.size	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMaxEv.constprop.14, .-_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMaxEv.constprop.14
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12, @function
_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12:
.LFB1577:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	24(%rdi), %rsi
	testq	%rsi, %rsi
	je	.L68
	movq	16(%rbx), %rax
	cmpq	%rsi, %rax
	je	.L69
.L57:
	movq	(%rbx), %r9
	leaq	0(,%rax,8), %rsi
	movl	0(%rbp), %ecx
	leaq	(%r9,%rsi), %rdx
	movl	%ecx, (%rdx)
	movq	8(%rbx), %rcx
	movl	%eax, 4(%rdx)
	movl	0(%rbp), %edi
	addq	%rcx, %rsi
	testq	%rax, %rax
	movl	%edi, (%rsi)
	movl	%eax, 4(%rsi)
	leaq	1(%rax), %rsi
	movq	%rsi, 16(%rbx)
	je	.L55
	leaq	-1(%rax), %rsi
	movl	(%rdx), %r10d
	movq	%rsi, %rdi
	shrq	%rdi
	cmpl	(%r9,%rdi,8), %r10d
	jae	.L58
	movl	4(%rdx), %r8d
	movq	%rax, %r11
.L60:
	leaq	-1(%r11), %rdx
	shrq	%rdx
	leaq	(%r9,%rdx,8), %rdi
	movq	(%rdi), %rbp
	movq	%rbp, (%r9,%r11,8)
	shrq	$32, %rbp
	testq	%rdx, %rdx
	movl	%r11d, 4(%rcx,%rbp,8)
	jne	.L70
.L59:
	movl	%r10d, (%rdi)
	movl	%r8d, 4(%rdi)
	movl	%edx, 4(%rcx,%r8,8)
.L58:
	testq	%rax, %rax
	je	.L55
	leaq	(%rcx,%rax,8), %rdx
	movq	%rsi, %rdi
	shrq	%rdi
	movl	(%rdx), %r8d
	cmpl	%r8d, (%rcx,%rdi,8)
	jae	.L55
	movl	4(%rdx), %edi
	movq	(%rbx), %r9
.L64:
	shrq	%rsi
	leaq	(%rcx,%rsi,8), %rdx
	cmpl	(%rdx), %r8d
	jbe	.L63
	movq	(%rdx), %r10
	movq	%r10, (%rcx,%rax,8)
	shrq	$32, %r10
	testq	%rsi, %rsi
	movl	%eax, 4(%r9,%r10,8)
	jne	.L71
.L65:
	movl	%r8d, (%rdx)
	movl	%edi, 4(%rdx)
	movl	%esi, 4(%r9,%rdi,8)
.L55:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L63:
	.cfi_restore_state
	leaq	(%rcx,%rax,8), %rdx
	movq	%rax, %rsi
	jmp	.L65
	.p2align 4,,10
	.p2align 3
.L71:
	movq	%rsi, %rax
	leaq	-1(%rsi), %rsi
	jmp	.L64
	.p2align 4,,10
	.p2align 3
.L70:
	leaq	-1(%rdx), %r11
	shrq	%r11
	cmpl	(%r9,%r11,8), %r10d
	jae	.L59
	movq	%rdx, %r11
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L68:
	movb	$1, %sil
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6resizeEm
	movq	24(%rbx), %rsi
	movq	16(%rbx), %rax
	cmpq	%rsi, %rax
	jne	.L57
.L69:
	addq	%rsi, %rsi
	movq	%rbx, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6resizeEm
	movq	16(%rbx), %rax
	jmp	.L57
	.cfi_endproc
.LFE1577:
	.size	_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12, .-_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1526:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1526
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	xorl	%edi, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$144, %rsp
	.cfi_def_cfa_offset 176
.LEHB0:
	call	_ZNSt8ios_base15sync_with_stdioEb
	leaq	104(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	call	_ZNSi10_M_extractImEERSiRT_
.L109:
	movq	104(%rsp), %rax
	leaq	-1(%rax), %rdx
	testq	%rax, %rax
	movq	%rdx, 104(%rsp)
	je	.L111
	leaq	112(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	movl	$1, %r12d
	xorl	%ebp, %ebp
	call	_ZNSi10_M_extractImEERSiRT_
.LEHE0:
	movq	112(%rsp), %rax
	movq	$0, (%rsp)
	movq	$0, 8(%rsp)
	movq	$0, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	.p2align 4,,10
	.p2align 3
.L107:
	leaq	-1(%rax), %rdx
	testq	%rax, %rax
	movq	%rdx, 112(%rsp)
	je	.L112
.L87:
	leaq	120(%rsp), %rsi
	movl	$_ZSt3cin, %edi
.LEHB1:
	call	_ZNSi10_M_extractImEERSiRT_
	testb	%r12b, %r12b
	jne	.L106
	jmp	.L108
	.p2align 4,,10
	.p2align 3
.L77:
	leaq	132(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	call	_ZNSi10_M_extractIjEERSiRT_
	leaq	132(%rsp), %rsi
	movq	%rsp, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12
.L106:
	movq	120(%rsp), %rax
	leaq	-1(%rax), %rdx
	testq	%rax, %rax
	movq	%rdx, 120(%rsp)
	jne	.L77
	movq	%rsp, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMaxEv.constprop.14
	movq	%rsp, %rdi
	movl	%eax, %ebx
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMinEv.constprop.13
	subl	%eax, %ebx
	movq	112(%rsp), %rax
	addq	%rbx, %rbp
	leaq	(%rax,%rax), %rdx
	cmpq	%rdx, 16(%rsp)
	jbe	.L107
	testq	%rax, %rax
	je	.L79
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L80:
	movq	%rsp, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMinEv.constprop.13
	leaq	140(%rsp), %rsi
	leaq	32(%rsp), %rdi
	movl	%eax, 140(%rsp)
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12
	movq	112(%rsp), %rax
	addq	$1, %rbx
	cmpq	%rax, %rbx
	jb	.L80
	testq	%rax, %rax
	je	.L79
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L81:
	movq	%rsp, %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMaxEv.constprop.14
	leaq	136(%rsp), %rsi
	leaq	64(%rsp), %rdi
	movl	%eax, 136(%rsp)
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12
	addq	$1, %rbx
	cmpq	112(%rsp), %rbx
	jb	.L81
.L79:
	movq	8(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L82
	call	_ZdaPv
.L82:
	movq	(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L83
	call	_ZdaPv
.L83:
	movq	112(%rsp), %rax
	xorl	%r12d, %r12d
	movq	$0, (%rsp)
	movq	$0, 8(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 16(%rsp)
	leaq	-1(%rax), %rdx
	testq	%rax, %rax
	movq	%rdx, 112(%rsp)
	jne	.L87
.L112:
	movq	%rbp, %rsi
	movl	$_ZSt4cout, %edi
	call	_ZNSo9_M_insertImEERSoT_
	leaq	132(%rsp), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	movb	$10, 132(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	64(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L88
	call	_ZdaPv
.L88:
	movq	72(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L89
	call	_ZdaPv
.L89:
	movq	32(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L90
	call	_ZdaPv
.L90:
	movq	40(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L91
	call	_ZdaPv
.L91:
	movq	(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L92
	call	_ZdaPv
.L92:
	movq	8(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L109
	call	_ZdaPv
	jmp	.L109
.L116:
	leaq	64(%rsp), %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMinEv.constprop.13
	leaq	132(%rsp), %rsi
	leaq	64(%rsp), %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12
.L108:
	movq	120(%rsp), %rax
	leaq	-1(%rax), %rdx
	testq	%rax, %rax
	movq	%rdx, 120(%rsp)
	je	.L113
	leaq	132(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	call	_ZNSi10_M_extractIjEERSiRT_
	movq	40(%rsp), %rdx
	movl	132(%rsp), %eax
	cmpl	%eax, (%rdx)
	ja	.L114
	movq	64(%rsp), %rdx
	cmpl	(%rdx), %eax
	jbe	.L108
	jmp	.L116
	.p2align 4,,10
	.p2align 3
.L114:
	leaq	32(%rsp), %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMaxEv.constprop.14
	leaq	132(%rsp), %rsi
	leaq	32(%rsp), %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE4pushERKj.constprop.12
	jmp	.L108
	.p2align 4,,10
	.p2align 3
.L113:
	leaq	64(%rsp), %rdi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMaxEv.constprop.14
	leaq	32(%rsp), %rdi
	movl	%eax, %ebx
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjE6popMinEv.constprop.13
.LEHE1:
	subl	%eax, %ebx
	movq	112(%rsp), %rax
	addq	%rbx, %rbp
	jmp	.L107
.L111:
	addq	$144, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L97:
	.cfi_restore_state
	movq	64(%rsp), %rdi
	leaq	72(%rsp), %rsi
	movq	%rax, %rbx
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjED2Ev.isra.10
	movq	32(%rsp), %rdi
	leaq	40(%rsp), %rsi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjED2Ev.isra.10
	movq	(%rsp), %rdi
	leaq	8(%rsp), %rsi
	call	_ZN12_GLOBAL__N_110MinMaxHeapIjjED2Ev.isra.10
	movq	%rbx, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
	.cfi_endproc
.LFE1526:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1526:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1526-.LLSDACSB1526
.LLSDACSB1526:
	.uleb128 .LEHB0-.LFB1526
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1526
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L97-.LFB1526
	.uleb128 0
	.uleb128 .LEHB2-.LFB1526
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1526:
	.section	.text.startup
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB1562:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE1562:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.weakref	_ZL20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_ZL27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_ZL27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_ZL22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_ZL20__gthrw_pthread_joinmPPv,pthread_join
	.weakref	_ZL21__gthrw_pthread_equalmm,pthread_equal
	.weakref	_ZL20__gthrw_pthread_selfv,pthread_self
	.weakref	_ZL22__gthrw_pthread_detachm,pthread_detach
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL19__gthrw_sched_yieldv,sched_yield
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL31__gthrw_pthread_mutex_timedlockP15pthread_mutex_tPK8timespec,pthread_mutex_timedlock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL29__gthrw_pthread_mutex_destroyP15pthread_mutex_t,pthread_mutex_destroy
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL27__gthrw_pthread_cond_signalP14pthread_cond_t,pthread_cond_signal
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL30__gthrw_pthread_cond_timedwaitP14pthread_cond_tP15pthread_mutex_tPK8timespec,pthread_cond_timedwait
	.weakref	_ZL28__gthrw_pthread_cond_destroyP14pthread_cond_t,pthread_cond_destroy
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.ident	"GCC: (Gentoo 4.6.3 p1.0, pie-0.5.1) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
