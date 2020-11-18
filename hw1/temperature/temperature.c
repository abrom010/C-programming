#include <stdio.h>
 /* print Fahrenheit-Celsius table
 for fahr = 0, 20, ..., 300; floating-point version */
main()
{
	float fahr, kelvin;
	float lower, upper, step;
	lower = 0; /* lower limit of temperatuire scale */
	upper = 100; /* upper limit */
	step = 10; /* step size */
	fahr = lower;

	while (fahr <= upper) {
		kelvin = (5.0/9.0) * (fahr-32.0) + 273.15;
		printf("%3.0f %6.1f\n", fahr, kelvin);
		fahr = fahr + step;
	}
}
