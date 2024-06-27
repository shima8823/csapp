/*

vcvtsi2ss xmm2 = (float) x
vmulss xmm1 = (float) x * y;
vunpcklps
vcvtps2pd xmm2 = (double) ((float) x * y);
vcvtsi2sdq xmm1 = (double) z
vdivsd xmm0 = w / z
vsubsd xmm0 = (double) ((float) x * y) - w / z

*/

double funct2(double w, int x, float y, long z) {
	return x * y - w / z;
}