/*
良問

L = sizoe(Type)
A.	&D[i][j]	= Xd + L(C ・ i + j)
	&D[i][j][k] = Xd + L(jの最大*kの最大*i  + kの最大*j + k)

*/

#define R 7
#define S 5
#define T 13

long A[R][S][T];

long store_ele(long i, long j, long k, long *dest) {
	*dest = A[i][j][k];
	return sizeof(A);
}