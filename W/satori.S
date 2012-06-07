	.file	"satori.cxx"
	.section	.text.hot,"ax",@progbits
	.p2align 4,,15
	.type	_ZN12_GLOBAL__N_1L12findSolutionEPNS_4ItemEh, @function
_ZN12_GLOBAL__N_1L12findSolutionEPNS_4ItemEh:
.LFB2161:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movl	%esi, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	testb	%sil, %sil
	jne	.L2
	movq	_ZN12_GLOBAL__N_1L20currentSolutionTimeCE(%rip), %rax
	cmpq	%rax, _ZN12_GLOBAL__N_1L16bestSolutionTimeE(%rip)
	ja	.L41
.L1:
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
.L2:
	.cfi_restore_state
	movzbl	%sil, %ebx
	leaq	0(,%rbx,8), %rdi
	call	_Znam
	xorl	%r8d, %r8d
	movq	%rax, %rbp
	.p2align 4,,10
	.p2align 3
.L13:
	movq	_ZN12_GLOBAL__N_1L20currentSolutionTimeAE(%rip), %r10
	movl	%r8d, %r9d
	movq	%r12, %rdx
	movq	%r12, %rcx
	xorl	%eax, %eax
	movq	%r10, %rdi
	.p2align 4,,10
	.p2align 3
.L4:
	movl	(%rcx), %esi
	addq	$1, %rax
	addq	$16, %rcx
	addq	%rsi, %rdi
	cmpq	%rax, %rbx
	ja	.L4
	movzbl	%r9b, %r11d
	movq	_ZN12_GLOBAL__N_1L20currentSolutionTimeBE(%rip), %rax
	movq	%r12, %rcx
	movq	%r11, %r15
	salq	$4, %r15
	addq	%r12, %r15
	movl	(%r15), %esi
	addq	%r10, %rsi
	cmpq	%rax, %rsi
	cmovb	%rax, %rsi
	xorl	%eax, %eax
	movq	%rsi, %r10
	.p2align 4,,10
	.p2align 3
.L5:
	movl	4(%rcx), %r14d
	addq	$1, %rax
	addq	$16, %rcx
	addq	%r14, %r10
	cmpq	%rax, %rbx
	ja	.L5
	movl	4(%r15), %eax
	movq	%r12, %rcx
	addq	%rax, %rsi
	movq	_ZN12_GLOBAL__N_1L20currentSolutionTimeCE(%rip), %rax
	cmpq	%rax, %rsi
	cmovb	%rax, %rsi
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L6:
	movl	8(%rcx), %r14d
	addq	$1, %rax
	addq	$16, %rcx
	addq	%r14, %rsi
	cmpq	%rax, %rbx
	ja	.L6
	movq	%r12, %rcx
	movq	$-1, %r14
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L8:
	movl	4(%rcx), %r15d
	cmpq	%r14, %r15
	jae	.L7
	cmpq	%rax, %r11
	cmovne	%r15, %r14
.L7:
	addq	$1, %rax
	addq	$16, %rcx
	cmpq	%rax, %rbx
	ja	.L8
	movq	$-1, %r15
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L10:
	movl	8(%rdx), %ecx
	cmpq	%rcx, %r15
	jbe	.L9
	cmpq	%rax, %r11
	cmovne	%rcx, %r15
.L9:
	addq	$1, %rax
	addq	$16, %rdx
	cmpq	%rax, %rbx
	ja	.L10
	addq	%r14, %rdi
	addq	%r15, %r10
	addq	%r15, %rdi
	cmpq	%rsi, %rdi
	jae	.L42
.L28:
	cmpq	%rsi, %r10
	jb	.L11
	cmpq	%r10, %rdi
	cmovbe	%r10, %rsi
.L11:
	movb	%r9b, 0(%rbp,%r8,8)
	movl	%esi, 4(%rbp,%r8,8)
	addq	$1, %r8
	cmpq	%r8, %rbx
	ja	.L13
	cmpq	$1, %rbx
	je	.L14
	leaq	-1(%rbx), %r9
	xorl	%esi, %esi
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L39:
	movq	%rsi, %rcx
	.p2align 4,,10
	.p2align 3
.L16:
	leaq	8(%rbp,%rcx,8), %rax
	addq	$1, %rsi
	cmpq	%r9, %rsi
	movq	%r8, (%rax)
	movb	%dil, (%rax)
	movl	%edx, 4(%rax)
	je	.L14
.L20:
	testq	%rsi, %rsi
	movq	8(%rbp,%rsi,8), %r8
	movzbl	8(%rbp,%rsi,8), %edi
	movl	12(%rbp,%rsi,8), %edx
	movq	%rsi, %rax
	js	.L39
	cmpl	%edx, 4(%rbp,%rsi,8)
	jbe	.L39
	.p2align 4,,10
	.p2align 3
.L29:
	movq	0(%rbp,%rax,8), %rcx
	movq	%rcx, 8(%rbp,%rax,8)
	subq	$1, %rax
	movq	%rax, %rcx
	js	.L16
	cmpl	%edx, 4(%rbp,%rax,8)
	jbe	.L16
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L42:
	cmpq	%r10, %rdi
	jb	.L28
	movq	%rdi, %rsi
	.p2align 4,,5
	jmp	.L11
.L14:
	movl	4(%rbp), %eax
	cmpq	_ZN12_GLOBAL__N_1L16bestSolutionTimeE(%rip), %rax
	jae	.L21
	movzbl	%r13b, %r15d
	subl	$1, %r13d
	leaq	8(%rbp), %r14
	subl	$1, %r15d
	movzbl	%r13b, %r13d
	movq	%rbp, %rdx
	movslq	%r15d, %r15
	movl	%r13d, 44(%rsp)
	xorl	%r13d, %r13d
	salq	$4, %r15
	.p2align 4,,10
	.p2align 3
.L22:
	movq	%r15, %rdi
	movq	%rdx, 32(%rsp)
	call	_Znam
	movq	32(%rsp), %rdx
	movq	%rax, %rsi
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L24:
	cmpq	%r13, %rcx
	je	.L23
	movzbl	0(%rbp,%rcx,8), %edi
	salq	$4, %rdi
	addq	%r12, %rdi
	movq	(%rdi), %r8
	movq	%r8, (%rsi)
	movq	8(%rdi), %rdi
	movq	%rdi, 8(%rsi)
	addq	$16, %rsi
.L23:
	addq	$1, %rcx
	cmpq	%rcx, %rbx
	ja	.L24
	movzbl	(%rdx), %ecx
	movq	_ZN12_GLOBAL__N_1L18currentSolutionTopE(%rip), %rsi
	movq	%rax, %rdi
	salq	$4, %rcx
	movzbl	12(%r12,%rcx), %ecx
	movb	%cl, (%rsi)
	movzbl	(%rdx), %ecx
	addq	$1, %rsi
	movq	%rsi, _ZN12_GLOBAL__N_1L18currentSolutionTopE(%rip)
	movq	_ZN12_GLOBAL__N_1L20currentSolutionTimeAE(%rip), %r9
	movq	_ZN12_GLOBAL__N_1L20currentSolutionTimeBE(%rip), %r8
	salq	$4, %rcx
	movl	(%r12,%rcx), %esi
	addq	%r9, %rsi
	movq	%rsi, _ZN12_GLOBAL__N_1L20currentSolutionTimeAE(%rip)
	movzbl	(%rdx), %ecx
	cmpq	%r8, %rsi
	cmovb	%r8, %rsi
	salq	$4, %rcx
	movl	4(%r12,%rcx), %ecx
	addq	%rcx, %rsi
	movq	_ZN12_GLOBAL__N_1L20currentSolutionTimeCE(%rip), %rcx
	movq	%rsi, _ZN12_GLOBAL__N_1L20currentSolutionTimeBE(%rip)
	movzbl	(%rdx), %edx
	cmpq	%rcx, %rsi
	cmovb	%rcx, %rsi
	salq	$4, %rdx
	movl	8(%r12,%rdx), %edx
	movq	%rax, 32(%rsp)
	movq	%rcx, 8(%rsp)
	movq	%r8, 16(%rsp)
	movq	%r9, 24(%rsp)
	addq	%rdx, %rsi
	movq	%rsi, _ZN12_GLOBAL__N_1L20currentSolutionTimeCE(%rip)
	movl	44(%rsp), %esi
	call	_ZN12_GLOBAL__N_1L12findSolutionEPNS_4ItemEh
	movq	24(%rsp), %r9
	movq	16(%rsp), %r8
	movq	8(%rsp), %rcx
	movq	32(%rsp), %rax
	subq	$1, _ZN12_GLOBAL__N_1L18currentSolutionTopE(%rip)
	movl	%r9d, %r9d
	movl	%r8d, %r8d
	movl	%ecx, %ecx
	testq	%rax, %rax
	movq	%r9, _ZN12_GLOBAL__N_1L20currentSolutionTimeAE(%rip)
	movq	%r8, _ZN12_GLOBAL__N_1L20currentSolutionTimeBE(%rip)
	movq	%rcx, _ZN12_GLOBAL__N_1L20currentSolutionTimeCE(%rip)
	je	.L25
	movq	%rax, %rdi
	call	_ZdaPv
.L25:
	addq	$1, %r13
	cmpq	%r13, %rbx
	jbe	.L21
	movq	%r14, %rdx
	addq	$8, %r14
	movl	4(%rdx), %eax
	cmpq	_ZN12_GLOBAL__N_1L16bestSolutionTimeE(%rip), %rax
	jb	.L22
.L21:
	testq	%rbp, %rbp
	je	.L1
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%rbp, %rdi
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
	jmp	_ZdaPv
.L41:
	.cfi_restore_state
	movq	%rax, _ZN12_GLOBAL__N_1L16bestSolutionTimeE(%rip)
	movq	_ZN12_GLOBAL__N_1L1nE(%rip), %rdx
	movq	_ZN12_GLOBAL__N_1L15currentSolutionE(%rip), %rsi
	movq	_ZN12_GLOBAL__N_1L12bestSolutionE(%rip), %rdi
	addq	$56, %rsp
	.cfi_def_cfa_offset 56
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
	jmp	memcpy
	.cfi_endproc
.LFE2161:
	.size	_ZN12_GLOBAL__N_1L12findSolutionEPNS_4ItemEh, .-_ZN12_GLOBAL__N_1L12findSolutionEPNS_4ItemEh
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB2163:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	xorl	%edi, %edi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	call	_ZNSt8ios_base15sync_with_stdioEb
	movq	%rsp, %rsi
	movl	$_ZSt3cin, %edi
	call	_ZNSi10_M_extractImEERSiRT_
	.p2align 4,,10
	.p2align 3
.L60:
	movq	(%rsp), %rax
	leaq	-1(%rax), %rdx
	testq	%rax, %rax
	movq	%rdx, (%rsp)
	je	.L61
	movl	$_ZN12_GLOBAL__N_1L1nE, %esi
	movl	$_ZSt3cin, %edi
	call	_ZNSi10_M_extractImEERSiRT_
	movq	_ZN12_GLOBAL__N_1L1nE(%rip), %rdi
	salq	$4, %rdi
	call	_Znam
	movq	_ZN12_GLOBAL__N_1L1nE(%rip), %rdi
	movq	%rax, %rbp
	testq	%rdi, %rdi
	je	.L45
	movq	%rax, %r12
	movq	%rax, %rbx
	xorl	%r13d, %r13d
	.p2align 4,,10
	.p2align 3
.L46:
	movq	%rbx, %rsi
	movl	$_ZSt3cin, %edi
	addq	$1, %r13
	call	_ZNSi10_M_extractIjEERSiRT_
	leaq	4(%rbx), %rsi
	movq	%rax, %rdi
	call	_ZNSi10_M_extractIjEERSiRT_
	leaq	8(%rbx), %rsi
	movq	%rax, %rdi
	addq	$16, %rbx
	call	_ZNSi10_M_extractIjEERSiRT_
	movq	_ZN12_GLOBAL__N_1L1nE(%rip), %rdi
	cmpq	%rdi, %r13
	jb	.L46
	testq	%rdi, %rdi
	je	.L45
	leaq	1(%rdi), %rdx
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L47:
	movb	%al, 12(%r12)
	addq	$1, %rax
	addq	$16, %r12
	cmpq	%rdx, %rax
	jne	.L47
.L45:
	call	_Znam
	movq	_ZN12_GLOBAL__N_1L1nE(%rip), %rdi
	movq	%rax, _ZN12_GLOBAL__N_1L12bestSolutionE(%rip)
	movq	$-1, _ZN12_GLOBAL__N_1L16bestSolutionTimeE(%rip)
	call	_Znam
	movzbl	_ZN12_GLOBAL__N_1L1nE(%rip), %esi
	movq	%rbp, %rdi
	movq	%rax, _ZN12_GLOBAL__N_1L15currentSolutionE(%rip)
	movq	%rax, _ZN12_GLOBAL__N_1L18currentSolutionTopE(%rip)
	movq	$0, _ZN12_GLOBAL__N_1L20currentSolutionTimeAE(%rip)
	movq	$0, _ZN12_GLOBAL__N_1L20currentSolutionTimeBE(%rip)
	movq	$0, _ZN12_GLOBAL__N_1L20currentSolutionTimeCE(%rip)
	call	_ZN12_GLOBAL__N_1L12findSolutionEPNS_4ItemEh
	movq	_ZN12_GLOBAL__N_1L16bestSolutionTimeE(%rip), %rsi
	movl	$_ZSt4cout, %edi
	call	_ZNSo9_M_insertImEERSoT_
	leaq	15(%rsp), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	movb	$10, 15(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	cmpq	$0, _ZN12_GLOBAL__N_1L1nE(%rip)
	je	.L48
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L49:
	movq	_ZN12_GLOBAL__N_1L12bestSolutionE(%rip), %rax
	movl	$_ZSt4cout, %edi
	movzbl	(%rax,%rbx), %esi
	addq	$1, %rbx
	call	_ZNSo9_M_insertImEERSoT_
	leaq	15(%rsp), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	movb	$32, 15(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	cmpq	_ZN12_GLOBAL__N_1L1nE(%rip), %rbx
	jb	.L49
.L48:
	leaq	15(%rsp), %rsi
	movl	$1, %edx
	movl	$_ZSt4cout, %edi
	movb	$10, 15(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	testq	%rbp, %rbp
	je	.L50
	movq	%rbp, %rdi
	call	_ZdaPv
.L50:
	movq	_ZN12_GLOBAL__N_1L12bestSolutionE(%rip), %rdi
	testq	%rdi, %rdi
	je	.L51
	call	_ZdaPv
.L51:
	movq	_ZN12_GLOBAL__N_1L15currentSolutionE(%rip), %rdi
	testq	%rdi, %rdi
	je	.L60
	call	_ZdaPv
	jmp	.L60
.L61:
	addq	$24, %rsp
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
.LFE2163:
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2355:
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
.LFE2355:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZN12_GLOBAL__N_1L1nE
	.comm	_ZN12_GLOBAL__N_1L1nE,8,8
	.local	_ZN12_GLOBAL__N_1L12bestSolutionE
	.comm	_ZN12_GLOBAL__N_1L12bestSolutionE,8,8
	.local	_ZN12_GLOBAL__N_1L16bestSolutionTimeE
	.comm	_ZN12_GLOBAL__N_1L16bestSolutionTimeE,8,8
	.local	_ZN12_GLOBAL__N_1L15currentSolutionE
	.comm	_ZN12_GLOBAL__N_1L15currentSolutionE,8,8
	.local	_ZN12_GLOBAL__N_1L18currentSolutionTopE
	.comm	_ZN12_GLOBAL__N_1L18currentSolutionTopE,8,8
	.local	_ZN12_GLOBAL__N_1L20currentSolutionTimeAE
	.comm	_ZN12_GLOBAL__N_1L20currentSolutionTimeAE,8,8
	.local	_ZN12_GLOBAL__N_1L20currentSolutionTimeBE
	.comm	_ZN12_GLOBAL__N_1L20currentSolutionTimeBE,8,8
	.local	_ZN12_GLOBAL__N_1L20currentSolutionTimeCE
	.comm	_ZN12_GLOBAL__N_1L20currentSolutionTimeCE,8,8
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
