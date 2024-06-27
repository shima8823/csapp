/*

Y86-64
rsum:
	pushq	%rbp
	rrmovq	%rsp, %rbp

	irmovq	$8, %r8
	irmovq	$1, %r9
	xorq	%rax, %rax // rax = 0
	andq	%rsi, %rsi // set CC(Condition Codes)
	jle		done
	mrmovq	(%rdi), %r10
	addq	%r8, %rdi
	subq	%r9, %rsi
	call	rsum
	addq	%r10, %rax
	done:
		popq	%rbp
		ret


ANSWER
	rbpはローカル変数を使用する時。

	rsum:
    pushq   %r10        # r10を保存（呼び出し先保存レジスタ）

    irmovq  $8, %r8     # 定数8をr8にロード
    irmovq  $1, %r9     # 定数1をr9にロード
    xorq    %rax, %rax  # rax = 0（戻り値の初期化）
    andq    %rsi, %rsi  # countの符号をチェック
    jle     done        # count <= 0 なら終了

    mrmovq  (%rdi), %r10  # *startの値をr10に読み込む
    addq    %r8, %rdi     # start+1
    subq    %r9, %rsi     # count-1

    pushq   %r10          # *startの値を保存
    call    rsum          # 再帰呼び出し
    popq    %r10          # *startの値を復元
    addq    %r10, %rax    # *start + 再帰呼び出しの結果

done:
    popq    %r10          # r10を復元
    ret

*/



long rsum(long *start, long count) {
	if (count <= 0)
		return 0;
	return *start + rsum(start+1, count-1);
}