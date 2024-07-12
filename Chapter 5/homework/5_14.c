/*

A. ループ・アンローリングをしてもクリティカル・パスの加算は必ず実行しなくてはならないため。
B. そもそものレイテンシ限界が3.00のため。

*/

typedef int data_t;
typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

void inner4(vec_ptr u, vec_ptr v, data_t *dest) {
	long i;
	long length = vec_length(u);
	data_t *udata = get_vec_start(u);
	data_t *vdata = get_vec_start(v);
	data_t sum = (data_t) 0;

	for (i = 0; i < length - 5; i += 6) {
		sum = sum + udata[i] * vdata[i];
		sum = sum + udata[i + 1] * vdata[i + 1];
		sum = sum + udata[i + 2] * vdata[i + 2];
		sum = sum + udata[i + 3] * vdata[i + 3];
		sum = sum + udata[i + 4] * vdata[i + 4];
		sum = sum + udata[i + 5] * vdata[i + 5];
	}
	for (; i < length; i++) {
		sum = sum + udata[i] * vdata[i];
	}

	*dest = sum;
}