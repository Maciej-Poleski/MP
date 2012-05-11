	.file	"satori.cxx"
	.text
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE6resizeEm.constprop.13, @function
_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE6resizeEm.constprop.13:
.LFB1556:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	leaq	0(,%rsi,4), %rdi
	call	_Znam
	testq	%rbp, %rbp
	movq	%rax, %r12
	je	.L2
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	movw	$0, (%r12,%rax,4)
	movw	$0, 2(%r12,%rax,4)
	addq	$1, %rax
	cmpq	%rbp, %rax
	jne	.L3
.L2:
	movq	8(%rbx), %rcx
	testq	%rcx, %rcx
	je	.L4
	movq	(%rbx), %rsi
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L5:
	movl	(%rsi,%rax,4), %edx
	movl	%edx, (%r12,%rax,4)
	addq	$1, %rax
	cmpq	%rcx, %rax
	jne	.L5
.L4:
	cmpq	$0, 16(%rbx)
	je	.L6
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L6
	call	_ZdaPv
.L6:
	movq	%rbp, 16(%rbx)
	movq	%r12, (%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1556:
	.size	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE6resizeEm.constprop.13, .-_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE6resizeEm.constprop.13
	.align 2
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12, @function
_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12:
.LFB1557:
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
	movq	16(%rdi), %rsi
	testq	%rsi, %rsi
	je	.L19
	movq	8(%rbx), %rdi
	cmpq	%rsi, %rdi
	je	.L20
.L12:
	movq	(%rbx), %rdx
	movl	0(%rbp), %eax
	testq	%rdi, %rdi
	leaq	(%rdx,%rdi,4), %rsi
	movl	%eax, (%rsi)
	je	.L13
	movzwl	(%rsi), %r9d
	movzwl	2(%rsi), %r8d
	leaq	-1(%rdi), %rax
	shrq	%rax
	leaq	(%rdx,%rax,4), %rcx
	movzwl	%r9w, %esi
	movzwl	%r8w, %r10d
	imulq	$2502, %rsi, %rsi
	addq	%r10, %rsi
	movzwl	2(%rcx), %r10d
	movl	_ZN12_GLOBAL__N_11HE(,%rsi,4), %ebp
	movzwl	(%rcx), %esi
	imulq	$2502, %rsi, %rsi
	addq	%r10, %rsi
	movq	%rdi, %r10
	cmpl	_ZN12_GLOBAL__N_11HE(,%rsi,4), %ebp
	jae	.L13
.L15:
	movl	(%rcx), %ecx
	testq	%rax, %rax
	movl	%ecx, (%rdx,%r10,4)
	jne	.L21
.L16:
	leaq	(%rdx,%rax,4), %rax
	movw	%r9w, (%rax)
	movw	%r8w, 2(%rax)
.L13:
	addq	$1, %rdi
	movq	%rdi, 8(%rbx)
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
.L21:
	.cfi_restore_state
	leaq	-1(%rax), %rsi
	shrq	%rsi
	leaq	(%rdx,%rsi,4), %rcx
	movzwl	(%rcx), %r10d
	movzwl	2(%rcx), %r11d
	imulq	$2502, %r10, %r10
	addq	%r11, %r10
	cmpl	_ZN12_GLOBAL__N_11HE(,%r10,4), %ebp
	jae	.L16
	movq	%rax, %r10
	movq	%rsi, %rax
	jmp	.L15
	.p2align 4,,10
	.p2align 3
.L19:
	movb	$1, %sil
	call	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE6resizeEm.constprop.13
	movq	16(%rbx), %rsi
	movq	8(%rbx), %rdi
	cmpq	%rsi, %rdi
	jne	.L12
.L20:
	movq	%rbx, %rdi
	addq	%rsi, %rsi
	call	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE6resizeEm.constprop.13
	movq	8(%rbx), %rdi
	jmp	.L12
	.cfi_endproc
.LFE1557:
	.size	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12, .-_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1504:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1504
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	xorl	%edi, %edi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$152, %rsp
	.cfi_def_cfa_offset 208
.LEHB0:
	call	_ZNSt8ios_base15sync_with_stdioEb
	leaq	56(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	call	_ZNSi10_M_extractImEERSiRT_
.L73:
	movq	56(%rsp), %rax
	leaq	-1(%rax), %rdx
	testq	%rax, %rax
	movq	%rdx, 56(%rsp)
	je	.L77
	movl	$_ZN12_GLOBAL__N_11nE, %esi
	movl	$_ZSt3cin, %edi
	call	_ZNSi10_M_extractImEERSiRT_
	movl	$_ZN12_GLOBAL__N_11mE, %esi
	movq	%rax, %rdi
	call	_ZNSi10_M_extractImEERSiRT_
	movq	_ZN12_GLOBAL__N_11mE(%rip), %r9
	movq	_ZN12_GLOBAL__N_11nE(%rip), %rdi
	xorl	%edx, %edx
	leaq	1(%r9), %rcx
	leaq	1(%rdi), %rsi
	movq	%rcx, %r8
	leaq	_ZN12_GLOBAL__N_11HE(,%rcx,4), %rax
	negq	%r8
	salq	$2, %r8
	.p2align 4,,10
	.p2align 3
.L24:
	addq	$1, %rdx
	movl	$-1, (%rax)
	movl	$-1, (%rax,%r8)
	addq	$10008, %rax
	cmpq	%rsi, %rdx
	jbe	.L24
	imulq	$10008, %rsi, %rsi
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L25:
	movl	$-1, _ZN12_GLOBAL__N_11HE(%rsi,%rax,4)
	movl	$-1, _ZN12_GLOBAL__N_11HE(,%rax,4)
	addq	$1, %rax
	cmpq	%rcx, %rax
	jbe	.L25
	testq	%rdi, %rdi
	movl	$1, %r12d
	je	.L27
.L69:
	testq	%r9, %r9
	movl	$1, %ebx
	je	.L30
	imulq	$2502, %r12, %rbp
	.p2align 4,,10
	.p2align 3
.L64:
	leaq	0(%rbp,%rbx), %rax
	movl	$_ZSt3cin, %edi
	addq	$1, %rbx
	leaq	_ZN12_GLOBAL__N_11HE(,%rax,4), %rsi
	call	_ZNSi10_M_extractIjEERSiRT_
	cmpq	_ZN12_GLOBAL__N_11mE(%rip), %rbx
	jbe	.L64
	movq	_ZN12_GLOBAL__N_11nE(%rip), %rdi
.L30:
	addq	$1, %r12
	cmpq	%rdi, %r12
	ja	.L29
	movq	_ZN12_GLOBAL__N_11mE(%rip), %r9
	jmp	.L69
.L29:
	testq	%rdi, %rdi
	je	.L27
	movq	_ZN12_GLOBAL__N_11mE(%rip), %rcx
	movl	$2502, %edx
	movl	$1, %esi
	.p2align 4,,10
	.p2align 3
.L31:
	testq	%rcx, %rcx
	je	.L33
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L32:
	movb	$0, _ZN12_GLOBAL__N_17visitedE(%rdx,%rax)
	addq	$1, %rax
	cmpq	%rcx, %rax
	jbe	.L32
.L33:
	addq	$1, %rsi
	addq	$2502, %rdx
	cmpq	%rdi, %rsi
	jbe	.L31
.L27:
	movl	$_ZN12_GLOBAL__N_11kE, %esi
	movl	$_ZSt3cin, %edi
	movl	$0, _ZN12_GLOBAL__N_111maxSolutionE(%rip)
	call	_ZNSi10_M_extractImEERSiRT_
	movl	$_ZN12_GLOBAL__N_11lE, %esi
	movq	%rax, %rdi
	call	_ZNSi10_M_extractImEERSiRT_
	movl	$_ZN12_GLOBAL__N_11xE, %esi
	movq	%rax, %rdi
	call	_ZNSi10_M_extractImEERSiRT_
	movl	$_ZN12_GLOBAL__N_11yE, %esi
	movq	%rax, %rdi
	call	_ZNSi10_M_extractImEERSiRT_
.LEHE0:
	movq	_ZN12_GLOBAL__N_11kE(%rip), %rax
	leaq	128(%rsp), %rsi
	leaq	16(%rsp), %rdi
	movq	$0, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movw	%ax, 128(%rsp)
	movq	_ZN12_GLOBAL__N_11lE(%rip), %rax
	movw	%ax, 130(%rsp)
.LEHB1:
	call	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12
	jmp	.L72
.L35:
	movq	32(%rsp), %rax
	cmpq	%rbp, %rax
	ja	.L78
.L41:
	movzwl	%r14w, %ebp
	movzwl	%r15w, %r12d
	movl	_ZN12_GLOBAL__N_111maxSolutionE(%rip), %ecx
	movslq	%ebp, %r13
	movslq	%r12d, %rbx
	imulq	$2502, %r13, %rax
	addq	%rbx, %rax
	movl	_ZN12_GLOBAL__N_11HE(,%rax,4), %edx
	movb	$1, _ZN12_GLOBAL__N_17visitedE(%rax)
	movzwl	%r14w, %eax
	cmpl	%edx, %ecx
	cmovae	%ecx, %edx
	cmpq	_ZN12_GLOBAL__N_11xE(%rip), %rax
	movl	%edx, _ZN12_GLOBAL__N_111maxSolutionE(%rip)
	je	.L79
.L42:
	leal	-1(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$2502, %rdx, %rdx
	cmpb	$0, _ZN12_GLOBAL__N_17visitedE(%rdx,%rbx)
	je	.L80
.L44:
	addl	$1, %ebp
	movslq	%ebp, %rax
	imulq	$2502, %rax, %rax
	cmpb	$0, _ZN12_GLOBAL__N_17visitedE(%rax,%rbx)
	je	.L81
.L45:
	imulq	$2502, %r13, %rdx
	leal	-1(%r12), %eax
	movslq	%eax, %rcx
	cmpb	$0, _ZN12_GLOBAL__N_17visitedE(%rcx,%rdx)
	je	.L82
.L46:
	imulq	$2502, %r13, %r13
	addl	$1, %r12d
	movslq	%r12d, %rax
	cmpb	$0, _ZN12_GLOBAL__N_17visitedE(%rax,%r13)
	je	.L83
.L72:
	movq	24(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L43
	movq	16(%rsp), %rax
	subq	$1, %rdi
	xorl	%ebp, %ebp
	testq	%rdi, %rdi
	movzwl	(%rax), %r14d
	movzwl	2(%rax), %r15d
	movq	%rdi, 24(%rsp)
	je	.L35
	movl	(%rax,%rdi,4), %edx
	cmpq	$1, %rdi
	leaq	0(,%rdi,4), %rbp
	movl	%edx, (%rax)
	je	.L35
	movzwl	(%rax), %edx
	movq	%rdi, %rbx
	xorl	%esi, %esi
	shrq	%rbx
	movw	%dx, 12(%rsp)
	movzwl	12(%rsp), %ecx
	movzwl	2(%rax), %edx
	imulq	$2502, %rcx, %rcx
	movw	%dx, 14(%rsp)
	movzwl	%dx, %edx
	addq	%rcx, %rdx
	movl	_ZN12_GLOBAL__N_11HE(,%rdx,4), %r11d
	jmp	.L40
.L85:
	leaq	(%rax,%r8,4), %r10
	movzwl	(%rdx), %r13d
	movzwl	(%r10), %r12d
	movzwl	2(%r10), %r9d
	imulq	$2502, %r13, %r13
	imulq	$2502, %r12, %r12
	addq	%r12, %r9
	movzwl	2(%rdx), %r12d
	movl	_ZN12_GLOBAL__N_11HE(,%r9,4), %r9d
	addq	%r13, %r12
	movl	_ZN12_GLOBAL__N_11HE(,%r12,4), %r12d
	cmpl	%r12d, %r9d
	jae	.L59
	movq	%r10, %rdx
	movq	%r8, %rcx
.L54:
	cmpl	%r9d, %r11d
	jb	.L84
.L38:
	movl	(%rdx), %r8d
	cmpq	%rcx, %rbx
	movl	%r8d, (%rax,%rsi,4)
	jbe	.L39
	movq	%rcx, %rsi
.L40:
	leaq	(%rsi,%rsi), %r8
	leaq	1(%r8), %rcx
	addq	$2, %r8
	cmpq	%r8, %rdi
	leaq	(%rax,%rcx,4), %rdx
	ja	.L85
	movzwl	(%rdx), %r9d
	movzwl	2(%rdx), %r8d
	imulq	$2502, %r9, %r9
	addq	%r9, %r8
	movl	_ZN12_GLOBAL__N_11HE(,%r8,4), %r9d
	cmpl	%r9d, %r11d
	jae	.L38
.L84:
	leaq	(%rax,%rsi,4), %rdx
.L39:
	movzwl	12(%rsp), %eax
	movw	%ax, (%rdx)
	movzwl	14(%rsp), %eax
	movw	%ax, 2(%rdx)
	movq	32(%rsp), %rax
	cmpq	%rbp, %rax
	jbe	.L41
.L78:
	movq	%rax, %rsi
	leaq	16(%rsp), %rdi
	shrq	%rsi
	call	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE6resizeEm.constprop.13
	jmp	.L41
.L59:
	movl	%r12d, %r9d
	jmp	.L54
.L82:
	leaq	80(%rsp), %rsi
	leaq	16(%rsp), %rdi
	movw	%r14w, 80(%rsp)
	movw	%ax, 82(%rsp)
	call	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12
	jmp	.L46
.L81:
	leaq	96(%rsp), %rsi
	leaq	16(%rsp), %rdi
	movw	%bp, 96(%rsp)
	movw	%r15w, 98(%rsp)
	call	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12
	jmp	.L45
.L80:
	leaq	112(%rsp), %rsi
	leaq	16(%rsp), %rdi
	movw	%ax, 112(%rsp)
	movw	%r15w, 114(%rsp)
	call	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12
	jmp	.L44
.L79:
	movzwl	%r15w, %eax
	cmpq	_ZN12_GLOBAL__N_11yE(%rip), %rax
	jne	.L42
.L43:
	movl	_ZN12_GLOBAL__N_111maxSolutionE(%rip), %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSo9_M_insertImEERSoT_
	leaq	143(%rsp), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	movb	$10, 143(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	16(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L73
	call	_ZdaPv
	jmp	.L73
	.p2align 4,,10
	.p2align 3
.L83:
	leaq	64(%rsp), %rsi
	leaq	16(%rsp), %rdi
	movw	%r14w, 64(%rsp)
	movw	%r12w, 66(%rsp)
	call	_ZN12_GLOBAL__N_14HeapISt4pairIttENS_10ComparatorEE4pushERKS2_.constprop.12
.LEHE1:
	jmp	.L72
.L77:
	addq	$152, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L61:
	.cfi_restore_state
	movq	16(%rsp), %rdi
	movq	%rax, %rbx
	testq	%rdi, %rdi
	je	.L53
	call	_ZdaPv
.L53:
	movq	%rbx, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
	.cfi_endproc
.LFE1504:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1504:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1504-.LLSDACSB1504
.LLSDACSB1504:
	.uleb128 .LEHB0-.LFB1504
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1504
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L61-.LFB1504
	.uleb128 0
	.uleb128 .LEHB2-.LFB1504
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1504:
	.section	.text.startup
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB1544:
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
.LFE1544:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZN12_GLOBAL__N_11nE
	.comm	_ZN12_GLOBAL__N_11nE,8,8
	.local	_ZN12_GLOBAL__N_11mE
	.comm	_ZN12_GLOBAL__N_11mE,8,8
	.local	_ZN12_GLOBAL__N_11HE
	.comm	_ZN12_GLOBAL__N_11HE,25040016,32
	.local	_ZN12_GLOBAL__N_17visitedE
	.comm	_ZN12_GLOBAL__N_17visitedE,6260004,32
	.local	_ZN12_GLOBAL__N_111maxSolutionE
	.comm	_ZN12_GLOBAL__N_111maxSolutionE,4,4
	.local	_ZN12_GLOBAL__N_11kE
	.comm	_ZN12_GLOBAL__N_11kE,8,8
	.local	_ZN12_GLOBAL__N_11lE
	.comm	_ZN12_GLOBAL__N_11lE,8,8
	.local	_ZN12_GLOBAL__N_11xE
	.comm	_ZN12_GLOBAL__N_11xE,8,8
	.local	_ZN12_GLOBAL__N_11yE
	.comm	_ZN12_GLOBAL__N_11yE,8,8
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
