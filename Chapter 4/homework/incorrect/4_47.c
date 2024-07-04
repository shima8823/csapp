// #include <stdio.h>
// #include <limits.h>
// #include <stdint.h>
// #include <stdbool.h>
// #include <assert.h>

// void bubble_a(long *data, long count) {
// 	long i, last;

// 	for (last = count-1; last > 0; last--) {
// 		for (i = 0; i < last; i++)
// 			if (data[i+1] < data[i]) {
// 				long t = data[i+1];
// 				data[i+1] = data[i];
// 				data[i] = t;
// 			}
// 	}
// }

// A
void bubble_a_pointer(long *data, long count) {
	long i, last;

	for (last = count-1; last > 0; last--) {
		for (i = 0; i < last; i++)
			if (*(data+i+1) < *(data+i)) {
				long t = *(data+i+1);
				*(data+i+1) = *(data+i);
				*(data+i) = t;
			}
	}
}

// int main() {
// 	long index[5] 	= { 9, 2, 5, 6, 3};
// 	long pointer[5] = { 9, 2, 5, 6, 3};

// 	bubble_a(index, 5);
// 	bubble_a_pointer(pointer, 5);

// 	printf("index 	");
// 	for (size_t i = 0; i < 5; i++) {
// 		printf("%ld ", index[i]);
// 	}
// 	printf("\n");
// 	printf("pointer ");
// 	for (size_t i = 0; i < 5; i++) {
// 		printf("%ld ", pointer[i]);
// 	}
// 	printf("\n");
	
// 	return 0;
// }