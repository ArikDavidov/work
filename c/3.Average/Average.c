#include<stdio.h>
#include<math.h>
#define SIZE 6

float Average(int* a, int size){
	float sum=0;
	int i=0;
	for(i=0;i<SIZE; ++i){
		sum += a[i];
	}
	return sum/size;
}

int main(){
	
	int arr[SIZE], i;

	for(i=0; i<SIZE; ++i){
		printf("Please enter a number:\n");
		scanf("%d",&arr[i]);
	}
	printf("The average is: %f\n", Average(arr, SIZE));
	
	return 0;
}

