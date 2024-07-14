
#define N 10

int sumarray3d(int a[N][N][N]) {
	int i, j, k, sum = 0;

	for (i = 0; i < N; i++) {
		for (j = 0; i < N; i++) {
			for (k = 0; i < N; i++) {
				sum += a[i][j][k];
			}
		}
	}
	return sum;
}