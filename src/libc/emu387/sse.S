/* Copyright (C) 2020 Ray Chason, see COPYING.DJ for details */

/* Return nonzero if we have SSE instructions */
    .text
    .globl __detect_sse
__detect_sse:
    /* Check EFLAGS bit 21; if we can change it, we have CPUID */
    push %ebx
    pushfl
    pop %eax
    mov %eax, %edx
    xor $0x00200000, %eax
    push %eax
    popfl
    pushfl
    pop %eax
    xor %edx, %eax
    and $0x00200000, %eax
    /* if we get zero, bit 21 didn't change; no CPUID and therefore no SSE */
    jz L_no_sse

    xor %eax, %eax
    cpuid
    /* Look for "GenuineIntel" */
    cmp $0x756E6547, %ebx
    jne L_not_intel
    cmp $0x6C65746E, %ecx
    jne L_not_intel
    cmp $0x49656E69, %edx
    je  L_cpu_ok /* matched */
L_not_intel:
    /* Look for "AuthenticAMD" */
    cmp $0x68747541, %ebx
    jne L_no_sse
    cmp $0x69746E65, %ecx
    jne L_no_sse
    cmp $0x444D4163, %edx
    jne L_no_sse /* else matched */
L_cpu_ok:
    cmp $1, %eax
    jb  L_no_sse /* function 1 not present */
    mov $1, %eax
    cpuid
    and $0x10180201, %ecx
    and $0x06000000, %edx
    mov %ecx, %eax
    or %edx, %eax

    pop %ebx
    ret

L_no_sse:
    /* No CPUID support, unknown CPU or function 1 not present */
    xor %eax, %eax
    pop %ebx
    ret
