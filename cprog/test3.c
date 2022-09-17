

#include <stdio.h>
#include <stdlib.h>

// Function that determine the size of the array from the first integer in the file
void read_array_size(FILE *file,int* size){
	fscanf(file,"%d",size);
}


// Function that will read the integers from the input file and store it in an array
void read_data_file(FILE *file,int data[],int size){
	//
	for(int i = 0; i < size; i++){
		fscanf(file,"%d",&data[i]);
	}
}

// Function that calculates the average and print it in stdout and the output file
void calculate_average(FILE *file,int data[],int size){
	double average = 0;
	for(int i=0; i < size; i++){
		average += data[i];
	}
	average /= size;
	printf("The calculated average is : %lf \n",average);
	fprintf(file,"The calculated average is : %lf \n",average);
}

// Function that calculates the maximum number in the array and print it in stdout and the output file
void calculate_maximum(FILE *file,int data[],int size){
	int max = data[0];
	for(int i=1; i < size; i++){
		if ( data[i] > max ){
			max = data[i];
		}
	}
	printf("The maximum number is : %d \n",max);
	fprintf(file,"The maximum number is : %d \n",max);
}

int main(int argc,char *argv[]){
	FILE *input , *output;
	// The script take one argument and that is the input file
	if ( argc < 2 ){
		printf("The program require two parameters the input file and the output file \n");
		exit(1);
	}
	int size;
	input = fopen(argv[1],"r+");
	int data[size];
	read_array_size(input,&size);
	read_data_file(input,data,size);
	fclose(input);
	//
	output = fopen("answer-hw3","w+");
	calculate_average(output,data,size);
	calculate_maximum(output,data,size);
	fclose(output);
	//
	return 0;
}