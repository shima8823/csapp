/*

難しいがプロセッサの仕組みを知る上で良問

irmovq $5, %rdx
irmovq $0x100, %rsp
rmmovq $rdx, 0(%rsp)
popq %rsp
nop
nop
rrmovq %rsp, %rax

*/