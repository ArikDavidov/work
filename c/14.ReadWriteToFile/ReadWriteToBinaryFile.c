#include <stdio.h>
#include <string.h>

int main(){
	FILE*	fp = NULL;
	char	str[128];
	int		i, *age, res = -1;
	int     nBytes, size;
	
	if((fp = fopen("PersonalData", "r")) != NULL){
		for(i = 0; i < 2; ++i)
		{
			printf("Please enter name and age of a person:")
			scanf("%s%d", str, age);
			fwrite(&nlng, sizeof(int), strlen(str), fp);
			fwrite(str, 1, strlen(str), fp);
			fwrite(&age, sizeof(int), 1, fp);
		}
		res = fclose(fp);
	}	
	if(res == 0)
	{
		if((fp = fopen("PersonalData", "r")) != NULL)
		{
			while(!feof(fp))
			{
				nBytes = fread(str, 1, strlen(str),fp);
				if (feof(fp)) 
				{
					break;
				}
			}
			res = fclose(fp);
		}
		else 
		{
			res = -1;
		}
	}
	return res;
}
