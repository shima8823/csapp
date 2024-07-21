#define M 214748364
#define N 214748364

int sumarrayrows(int a[M][N]) {
	int i, j, sum = 0;

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++)
			sum += a[i][j];
	}
	return sum;
}

int sumarraycols(int a[M][N]) {
	int i, j, sum = 0;

	for (j = 0; j < N; j++) {
		for (i = 0; i < M; i++)
			sum += a[i][j];
	}
	return sum;
}

#include <stdio.h>
#include <time.h>
int main() {
    int a[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = i + j; // 配列に適当な値を入れる
        }
    }

    clock_t start, end;
    double cpu_time_used;

    // sumarrayrows 関数の実行時間を計測
    start = clock();
    int sum_rows = sumarrayrows(a);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("sumarrayrows: %f seconds\n", cpu_time_used);

    // sumarraycols 関数の実行時間を計測
    start = clock();
    int sum_cols = sumarraycols(a);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("sumarraycols: %f seconds\n", cpu_time_used);

    return 0;
}