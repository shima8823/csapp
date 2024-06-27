/*

A.	引数が1個だった場合xmmのindex順にxmm0, xmm1に格納される。
	2個だった場合はxmm0, xmm1でひとまとまり、xmm2,xmm3でひとまとまりというようになる。
B.	xmm0とxmm1に上位下位ビット分けて返される。
	xmm0はreal部、xmm1はimg部

*/