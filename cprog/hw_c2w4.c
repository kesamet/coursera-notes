#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void read_array_size(FILE *fptr, int *size)
{
    fscanf(fptr, "%d", size);
}

// Read data
void read_data(FILE *fptr, int data[], int size)
{
    int i;
    for(i = 0; i < size; i++) {
        fscanf(fptr, "%d", &data[i]);
    }
}

// Print data
void print_data(int d[], int size)
{
    int i;
    for(i=0; i<size; i++) {
        printf("%d\t", d[i]);
        if((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}

// Compute average. First entry of data is the size of array
double average(int data[], int size)
{
    int i;
    double avg = 0.0;
    for(i = 0; i < size; i++) {
        avg += data[i];
    }
    return avg / size;
}

// Compute maximum. First entry of data is the size of array
int maximum(int data[], int size)
{
    int i, max = 0;
    for(i = 0; i < size; i++) {
        if(data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

// Write outputs
void write_outputs(FILE *ofp, int data[], int size)
{
    double avg_val = average(data, size);
    printf(" Average = %lf\n", avg_val);
    fprintf(ofp, " Average = %lf\n", avg_val);

    int max_val = maximum(data, size);
    printf(" Maximum = %d\n", max_val);
    fprintf(ofp, " Maximum = %d\n", max_val);
}

int main(int argc, char *argv[])
{
    int size;
    int data[size];
    FILE *ifp, *ofp;
    
    if(argc != 2) {
        printf("Need 'executable inputfile'\n");
        exit(1);
    }

    ifp = fopen(argv[1], "r+");
    if (ifp == NULL) {
        printf("File not found\n");
        exit(1);
    }
    
    read_array_size(ifp, &size);
    printf("size = %d\n", size);
    read_data(ifp, data, size);

    printf("Inputs:\n");
    print_data(data, size);

    ofp = fopen("answer-hw3", "w+");
    write_outputs(ofp, data, size);

    fclose(ifp);
    fclose(ofp);
    return 0;
}
