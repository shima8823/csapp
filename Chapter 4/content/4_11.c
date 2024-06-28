/*

word Min3 = [
	A <= B && A <= C : A;
	B <= A && B <= C : B;
	1				 : C;
];

A = 2
B = 1
C = 3

[1 <= 3 : B]

A = 3
B = 2
C = 1

[ C]

word Min3 = [
	A <= B && A <= C : A;
	B <= C : B;
	1				 : C;
];


*/