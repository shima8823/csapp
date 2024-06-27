/*

vmovss		xmm1 = *dp
vcvtsi2sd	xmm2 = (double) *ap
vucomisd	b comp (double) *ap
jbe .L8		b <= (double) *ap
vcvtsi2ssq	xmm0 = (float) c
vmulss		xmm1 = (float) c * (*dp)
vunpcklps
vcvtps2pd	xmm0 = (double) ((float) c * (*dp))
ret

.L8
vaddss		xmm1 = *dp + *dp
vcvtsi2ssq	xmm0 = (float) c
vaddss		xmm0 = (float) c + (*dp + *dp)
vunpcklps	
vcvtps2pd	xmm0 = (double) ((float) c + (*dp + *dp))
ret

*/

double funct3(int *ap, double b, long c, float *dp) {
	if (b <= *ap)
		return c + (*dp + *dp);
	return c * *dp;
}