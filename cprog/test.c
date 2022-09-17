#include<stdio.h>

typedef enum choices {left, left_center = 2, right_center, right = 5} choices;

int foobar(int* n){
     *n = *n +1;
     return *n;
}

void swap(int *i, int *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

int main(void)
{
    // int a = 1, b = 2, c = 3;
    // int i = 0, j = 1, k = 2;
    // int v =  (i && (j = k)) || (k > j);
    // printf("%d\n\n", v);

    // int k = 6;
    // printf("foobar(k) = %d,", foobar(&k) );
    // printf(" k = %d\n", k);

    // int a[10] = {1,2,3,4,5,6,7,8,9,10}, i = 6 ;
    // int *p = &a[0];
    // // printf("%d\n", &a[0]);
    // printf("%d\n", *p);
    // printf("%d\n", *(p + i));

    // char a[5] = {"a" "b" "c" "d" "e"};
    // char* str = & a[0];
    // printf("%c\n", *str);

    // double x = 1.2, y = 3.4;
    // double *p = &x;
    // double *q = &y;
    
    // p = &5.15;
    // p = (int)q;
    // q = &p;
    // y = *q;
    // printf("%f", y);

    struct complex{ double real;  double imaginary;}  c1 = {1.5,  -2.0}, c2;
    struct complex *ptr_c = &c1;
    printf("%20lf\n", c1.real);
    printf("%f\n", ptr_c -> real);

    enum choices x = right_center;
    printf("%d\n", x);

    int a = 2, b = 3;
    printf("%d %d\n", a, b);
    swap(&a, &b);
    printf("%d %d\n", a, b);

    return 0;
}
