#include <stdio.h>
#include <ctype.h>

typedef enum month{ jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec } month;
typedef struct date{ month m; int d; } date;

// Get nuuber of days in given month
int numofdays(month m)
{
    switch(m)
    {
        case feb: return 28; break;
        case apr: return 30; break;
        case jun: return 30; break;
        case sep: return 30; break;
        case nov: return 30; break;
        default: return 31; break;
	}
}

// Get next day
date nextday(date x)
{
    if(x.d < numofdays(x.m)){
        x.d++;
    }else{
        x.d = 1;
        x.m = (x.m + 1) % 12;
    }
    return x;
}

// Print date
void printdate(date x)
{
    switch(x.m)
    {
        case jan: printf(" January "); break;
        case feb: printf(" February "); break;
        case mar: printf(" March "); break;
        case apr: printf(" April "); break;
        case may: printf(" May "); break;
        case jun: printf(" June "); break;
        case jul: printf(" July "); break;
        case aug: printf(" August "); break;
        case sep: printf(" September "); break;
        case oct: printf(" October "); break;
        case nov: printf(" November "); break;
        case dec: printf(" December "); break;
    }
	printf("%d\n", x.d);
}

// Pretty print
void prettyprint(date x)
{
    printdate(x);
    printf(" Next date :");
    printdate(nextday(x));
    printf("\n");
}

int main(void)
{
    date x1 = {feb, 28};
    prettyprint(x1);

    date x2 = {mar, 14};
    prettyprint(x2);

    date x3 = {oct, 31};
    prettyprint(x3);

    date x4 = {dec, 31};
    prettyprint(x4);

    return 0;
}
