/*



*/

#define N 16
typedef int fix_matrix[N][N];

// void fix_set_diag(fix_matrix A, int val) {
// 	long i = 0;

// 	do {
// 		**(A + i) = val;
// 		// i = , j = 1
// 		i += 4 * (N * 1 + 1);
// 	} while (i != 4 * (N * N + N));
// }

void fix_set_diag_correct(fix_matrix A, int val) {
	long i = 0;

	do {
		**(A + i) = val;
		// i = , j = 1
		i += (N + 1);
	} while (i != N * (N + 1));
}

int main() {

}