#include<stdio.h>
#include<math.h>

int Prime(int n){
	int div;
	if(n<=0){
		printf("Prime function: Illegal input\n");
		return -1;
	}
	if (n>=4){
		if(n%2==0){
			printf("Your number is not a prime number\n");
			return 0;
		}
		for(div=3; div<=sqrt(n); div+=2){
			if(n%div==0){
				printf("Your number is not a prime number\n");
				return 0;
			}
			printf("Your number is a prime number\n");
			return 1;
		}
	}
	else{
		printf("Your number is a prime number\n");
		return 1;
	}	
}


int Palindrome(int n){

	int len=0, i=0, j=0;
	int div = n, rDigit = n, lDigit = n;

	if(n<=0){
		printf("Palindrome function: Illegal input\n");
		return -1;
	}
	while(div>0){
		div /= 10;
		len += 1;
	}
	rDigit = n;
	for(i=0; i<len/2; ++i){
		lDigit = n;
		for(j=0;j<len-1-i;++j){
			lDigit/=10;			
		}
		lDigit %= 10;
		if((lDigit %= 10)!=(rDigit %= 10)){
			printf("Your number is not a Palindrom\n");
			return 0;
		}
		rDigit /= 10;
	}
	printf("Your number is a Palindrom\n");
	return 1;
		
}

int Ascend(int n){
	int rDigit;
	if (n<9){
		printf("Ascend function: Illegal input\n");
		return -1;
	}
		
	do{
		rDigit = n % 10;
		n /= 10;
		if(rDigit <= n % 10){
			printf("Your number is not in ascending order\n");
			return 0;
		}
	} while (n>0);

	printf("Your number is in ascending order\n");
	return 1;
}

int Reverse(int n){

	int result=0, curentDigit=0;

	if (n<0){
		printf("Reverse function: Illegal input\n");
		return -1;
	}

	do{
		curentDigit = n % 10;
		result = result * 10 + curentDigit;
		n /= 10;		
	} while (n>0);

	printf("Your number in reverse order is: %d\n", result);
	return result;
}

int main(){
	
	int n;

	printf("Please enter a number:\n");
	scanf("%d",&n);

	Prime(n);
	Palindrome(n);
	Ascend(n);
	Reverse(n);
	
	return 0;
}

