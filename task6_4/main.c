#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char c;
	int fd1;
	fd1 = open("//home/ndm/os2018/passwd", O_RDONLY);
	if(fd1 == -1)
	{
		err(1, "%s", "//home/ndm/os2018/passwd");
	}

	int fd2;
	fd2 = open ("//home/ndm/passwd1", O_CREAT | O_WRONLY);
	if(fd2 == -1)
	{
		err(2, "%s", "//home/ndm/passwd1");
		close(fd1);
	}
	while(read(fd1, &c, 1))
	{
		if( c == ':') c = '?';

		write(fd2, &c, 1);
	}

	close(fd1);
	close(fd2);


	exit(0);
}


