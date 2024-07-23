// Blocking
void traspose(int *dst, int *src, int dim) {
	int i, j;

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[i*dim +j];
}

// 2 * 2 unrolling
void traspose(int *dst, int *src, int dim) {
	int i, j;

	int a[dim];

	for (i = 0; i < dim - 1; i++) {
		for (j = 0; j < dim - 1; j+=2) {
			a[j*dim + i] = src[i*dim +j];
			a[(j+1)*dim + i] = src[i*dim +(j+1)];
		}
		for (; j < dim; j++)
			a[j*dim + i] = src[i*dim +j];
	}

	dst = a;
}