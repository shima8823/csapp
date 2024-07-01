/*

間違ってはないと思う。valAが1個上のパイプで変更された、パイプラインレジスタEの値を取得してしまう

irmovq $5, %rdx
irmovq $0x100, %rsp
rmmovq $rdx, 0(%rsp)
popq %rsp				F D E M W
rrmovq %rsp, %rax		  F D E M W

*/