#include <stdio.h>
#include <stdlib.h>

void print_file(FILE *fptr)
{
    int c;
    rewind(fptr);
    while((c = getc(fptr)) != EOF) {
        putc(c, stdout);
    }
}

void double_space(FILE *ifp, FILE *ofp)
{
    int c;
    rewind(ifp);
    while((c = getc(ifp)) != EOF) {
        putc(c, ofp);
        if(c == "\n") {
            putc("\n", ofp);
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *ifp, *ofp;

    if(argc != 3) {
        printf("Need executable inputfile outputfile");
        exit(1);
    }

    ifp = fopen(argv[1], "r+");
    ofp = fopen(argv[2], "w+");
    printf("%s", argv[1]);
    print_file(ifp);
    printf("\n\n");
    double_space(ifp, ofp);
    printf("%s", argv[2]);
    print_file(ofp);
    printf("\n\n");
    fclose(ifp);
    fclose(ofp);
    return 0;
}