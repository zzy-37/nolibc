.intel_syntax noprefix

#define def_syscall(name, num) \
.global name; \
name:; \
        mov rax, num; \
        mov r10, rcx; \
        syscall; \
        ret

def_syscall(read, 0)
def_syscall(write, 1)
def_syscall(exit, 60)

.global _start
_start:
        xor rbp, rbp
        pop rdi
        mov rsi, rsp
        call main
        mov rdi, rax
        call exit
