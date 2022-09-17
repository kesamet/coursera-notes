#include <stdio.h>
#include <math.h>

// Returns the sine of a value between 0 and 1
int main(void)
{
    double x;
    printf("Enter a value between 0 and 1: ");
    scanf("%lf", &x);
    printf("sin(x) = %lf \n\n", sin(x));
    return 0;
}
