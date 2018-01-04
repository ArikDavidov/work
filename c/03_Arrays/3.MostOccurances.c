#include<stdio.h>
#define SIZE 8

int Max(int* a, int size){
	int i=0, j=0, maxVal=0, currentCount=1, maxCount=0;
	for(i=0; i<SIZE-2; ++i){
		currentCount=1;
		if(i==0 || a[i]!=maxVal){
			for(j=i+1; j<SIZE-1; ++j){
				if(a[j]==a[i]){
					currentCount += 1;
				}
			}
			if(currentCount > maxCount){
				maxCount = currentCount;
				maxVal=a[i];
			}
		}
	}
	return maxVal;
}

int main(){
	
	int arr[SIZE], i;
	for(i=0; i<SIZE; ++i){
		printf("Please enter a number:\n");
		scanf("%d",&arr[i]);
	}

	printf("\nMost occurances: %d\n", Max(arr, SIZE));
	
	return 0;
}
