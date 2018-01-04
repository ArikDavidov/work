#include<stdio.h>

int func1(int N){
	int lineNum, NStars;
	printf("\n");
	for(lineNum=0; lineNum<N; ++lineNum){
		for(NStars=0; NStars<lineNum+1; ++NStars){
			printf("*");
		}
		printf("\n");
	}
}

int func2(int N){
	int lineNum, NStars;
	func1(N);
	for(lineNum=N-1;lineNum>0; --lineNum){
		for(NStars=lineNum; NStars>0; --NStars){
			printf("*");
		}
		printf("\n");		
	}
}

int func3(int N){
	int lineNum, NStars, NBlanks;
	for(lineNum=0; lineNum<N; ++lineNum){
		for(NBlanks=N-lineNum-1; NBlanks>0; --NBlanks){
			printf(" ");
		}
		for(NStars=0; NStars<lineNum*2+1; ++NStars){
			printf("*");
		}
		printf("\n");
	}
}

int main(){
	int N;
	printf("Please enter number of stars (3-50):\n");
	scanf("%d",&N);
	if (N>50 || N<3){
		return -1;
	}
	
	func1(N);
	func2(N);
	func3(N);
	
	return 0;
}
