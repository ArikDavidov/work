#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int fd;
	char str[] = "Arik_42!!!!!!!!!!";
	void* ptr = NULL;
	
	if (-1 == (fd = open("myfile.txt", O_WRONLY)))
	{
		perror("open");
		exit(EXIT_FAILURE);
	}	

	ptr = mmap(NULL, 128, PROT_WRITE, MAP_SHARED, fd, 0);
	

	write(fd, str, 8);

	fsync(fd);	
	close (fd);
	
	return 0;

}


