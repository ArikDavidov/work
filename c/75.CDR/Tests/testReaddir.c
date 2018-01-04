#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>


int main()
{
	DIR* dirp = NULL;
	struct dirent* dp;

	dirp = opendir("./Input");

	while (dirp)
	{
		errno = 0;
		if (NULL == (dp = readdir(dirp)))
		{
			usleep(4000000);
			rewinddir(dirp);
			continue;
		}
		
		/*moveToWorkInProgressDir*/
		printf("%s\n", dp->d_name);
	}


	closedir(dirp);

	return 0;
}
