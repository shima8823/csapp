/*

面白問題

A.	CD間にレジスタを挿入する
	スループット	: (1 / 190) * (1000 / 1) = 5.26 GIPS
	ps / stage		: 190 ps(pico second)
	レイテンシ		: 190 * 2 = 380 ps
B.	BC間, DE間
	スループット	: (1 / 130) * (1000 / 1) = 7.69 GIPS
	ps / stage		: 130 ps(pico second)
	レイテンシ		: 130 * 3 = 390 ps
C.	AB間, CD間, DE間
	スループット	: (1 / 110) * (1000 / 1) = 9.09 GIPS
	ps / stage		: 110 ps(pico second)
	レイテンシ		: 110 * 4 = 440 ps
D.	5
	スループット	: (1 / 100) * (1000 / 1) = 10 GIPS
	ps / stage		: 100 ps(pico second)
	レイテンシ		: 100 * 5 = 500 ps


*/