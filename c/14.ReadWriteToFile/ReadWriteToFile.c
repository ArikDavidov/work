#include <stdio.h>
#include <string.h>

int main()
{
	FILE*	fp = NULL;
	char	str[128];
	int		i, age, res = -1;

	if((fp = fopen("PersonalData", "r")) != NULL)
	{
		for(i = 0; i < 2; ++i)
		{
			printf("Please enter name and age of a person:")
			scanf("%s%d", str, age);
			fprintf(fp, "%s %d\n", name, age);
		}
		res = fclose(fp);
	}
	if(res == 0){
		if((fp = fopen("PersonalData", "r")) != NULL)
		{
			while(!feof(fp))
			{
				str = fscans(fp, "%s%d");
				if (feof(fp))
				{
					break;
				}
				printf("Name = %s Age = %d\n", str);
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

