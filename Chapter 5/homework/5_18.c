double poly(double a[], double x, long degree) {
	long i;
	double result = a[0];
	double xpwr = x;
	for (i = 1; i <= degree; i++) {
		result += a[i] * xpwr;
		xpwr = x * xpwr;
	}
	return result;
}

//ループアンローリング
double polyl(double a[], double x, long degree) {
	long i;
	double result = a[0];
	double xpwr = x;
	for (i = 1; i < degree-1; i+=2) {
		result = result + a[i] * xpwr + a[i+1] * (xpwr*x);
		xpwr = x*x * xpwr;
	}

	for (; i <= degree; i++) {
		result += a[i] * xpwr;
		xpwr = x * xpwr;
	}
	return result;
}

//並列累積機
double polyp(double a[], double x, long degree) {
	long i;
	double result = a[0];
	double result1 = 0;
	double xpwr = x;
	for (i = 1; i <= degree-1; i+=2) {
		result = result + a[i] * xpwr;
		result1 = result1 + a[i+1] * (xpwr*x);
		xpwr = x*x * xpwr;
	}

	for (; i <= degree; i++) {
		result += a[i] * xpwr;
		xpwr = x * xpwr;
	}

	return result + result1;
}

//再結合
double polyp(double a[], double x, long degree) {
	long i;
	double result = a[0];
	double result1 = 0;
	double xpwr = x;
	for (i = 1; i <= degree-1; i+=2) {
		result = result + a[i] * xpwr;
		result1 = result1 + a[i+1] * (xpwr*x);
		xpwr = xpwr * (x*x);
	}

	for (; i <= degree; i++) {
		result += a[i] * xpwr;
		xpwr = x * xpwr;
	}

	return result + result1;
}

// Horner法
double poly_horer(double a[], double x, long degree) {
	long i;
	double result = a[degree];
	double result1 = a[degree-1];
	double xpwr = x;
	for (i = degree-1; i >= 1; i-=2) {
		result = a[i] + x*result;
		result1 = a[i-1] + x*result1;
	}
	return result + result1;
}
