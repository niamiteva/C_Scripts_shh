#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		errx(1, "err");
	}
	
	int fd1;
        fd1 = open(argv[1], O_RDONLY);
        if(fd1 == -1)
        {
		err(2, "%s", argv[1]);
        }

	struct stat sb;
	stat(argv[2], &sb);
        char c;	
	if(S_ISDIR(sb.st_mode))
	{
		int size1 = strlen(argv[1]);
		char name[size1+1];
		strcpy(name, argv[1]);
	
		int size2 = strlen(argv[2]);
		char dir[size1+size2+1];
		strcpy(dir, argv[2]);
		strcat(dir,"/");
		strcat(dir, name);

		int fd2;
		fd2 = open(dir, O_CREAT | O_WRONLY | O_TRUNC);
		if(fd2 == -1 )
		{
			err(2, "%s", dir);
			close(fd1);
		}

		while(read(fd1, &c, 1))
                {
                        write(fd2, &c, 1); 
                }

		close(fd2);
	}
	else if(S_ISDIR(sb.st_mode))
	{
		int fd3;
		fd3 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC);
		if(fd3 == -1)
		{
			err(3, "%s", argv[2]);
			close(fd1);
		}

		while(read(fd1, &c, 1))
		{
			write(fd3, &c, 1);
		}
		close(fd3);
	}
	else
	{
		errx(4, "argv 2 not file not dir");
	}

	close(fd1);

	exit(0);
}



