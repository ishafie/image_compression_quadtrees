#include <math.h>
#include <stdio.h>

int main(void)
{
	double calc;
	
	double a1, a2, b1, b2, r1, r2, g1, g2;
	a1 = 255;
	a2 = 120;
	b1 = 200;
	b2 = 4;
	r1 = 0;
	r2 = 0;
	g1 = 12;
	g2 = 15;
	
	double powr = (r1 - r2) * (r1 - r2);
	double powg = (g1 - g2) * (g1 - g2);
	double powb = (b1 - b2) * (b1 - b2);
	double powa = (a1 - a2) * (a1 - a2);
	
	calc = sqrt(powr + powg + powb + powa);
	printf("calc = %f\n", calc);
	return (0);
}
