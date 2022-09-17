#include<stdio.h>
#include<math.h>

// prints a table of values for sine and cosine between (0, 1)
int main(void)
{ 
    double x;
    for(int i = 0; i <= 10; i++) {
        x = i / 10.0;
        printf("sin(%lf) = %lf, cos(%lf) = %lf\n", x, sin(x), x, cos(x));
    }
    return 0;
}
