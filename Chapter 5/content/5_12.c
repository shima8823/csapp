// ubuntu cc -S 5_12.c -mavx -Og

void psum1(float a[], float p[], long n) {
	long i;
	p[0] = a[0];
	for (i = 1; i < n; i++)
		p[i] = p[i-1] + a[i];
}

void not_depend_psum1(float a[], float p[], long n) {
	long i;
	p[0] = a[0];
	for (i = 1; i < n; i++) {
		float t = p[i-1];
		p[i] = t + a[i];
	}
}

// ans
void psum1a(float a[], float p[], long n) {
	long i;
	float last_val, val;
	last_val = p[0] = a[0];
	for (i = 1; i < n; i++) {
		val = last_val + a[i];
		p[i] = val;
		last_val = val;
	}
}