#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		errx(1, "err");
	}
	
	struct stat sb;
	stat(argv[argc-1], &sb);
	if(!S_ISDIR(sb.st_mode))
	{
		errx(2, "not dir");
	}

	int fd1;
	int j =2;
	for(int i=1; i<argc-1; i++)
	{
		fd1 = open(argv[i], O_RDONLY);
		if(fd1 == -1)
		{
			j++;
			err(j, "%s", argv[i]);
		}
		
		int size1 = strlen(argv[i]);
                char name[size1+1];
                strcpy(name, argv[i]);

                int size2 = strlen(argv[argc -1]);
                char dir[size1+size2+2];
                strcpy(dir, argv[argc-1]);
                strcat(dir,"/");
                strcat(dir, name);

                int fd2;
                fd2 = open(dir , O_CREAT | O_WRONLY | O_TRUNC);
                if(fd2 == -1 )
                {
                        err(++j, "%s", dir);
                        close(fd1);
                }
		
		char c;
                while(read(fd1, &c, 1))
                {
                        write(fd2, &c, 1);
                }

                close(fd2);
		close(fd1);
	
	}
	exit(0);
}

