#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>


int main(int argc, char* argv[])
{
	char c;
	if(argc == 1)
	{
		errx(1, "err");
	}
	
	int fd;
	for(int i=1; i<argc; i++)
	{
		fd = open(argv[i], O_RDONLY);
		if(fd == -1)
		{
			err(2, "%s", argv[i]);
		}	
		while (read(fd, &c, 1))
		{
			write(1, &c, 1);
		}
	}

	exit(0);
}



