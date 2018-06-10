#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//#include <err.h> // can we use this instead of write(2, " ",1)



int main(int argc, char* argv[])
{
        if(argc != 3)
        {
                write(2, "Too few arguments\n", 18);
                exit(-1);
        }

        int fd = open(argv[1], O_RDONLY);
        if(fd == -1 )
        {
                write(2, "Enable to open file\n", 20);
                exit(-1);
        }
        
        off_t start = lseek(fd, 0, SEEK_SET);
        off_t end = lseek(fd, 0, SEEK_END);
        off_t midd;

        char wbuf[64];//word
        char mbuf[1024];//meaning
        int cmp;
        int found = 0;

        while (start <= end)
        {
                midd = (start + end )/2;
                lseek(fd, midd, SEEK_SET);

                char c;
                while(read(fd, &c, 1) >0)
                {
                        if(c == '\0') break;
                }

                ssize_t nchr =0;
                ssize_t indx = 0;
                char *p = NULL;
                if(read(fd, &wbuf, sizeof(wbuf)) == -1)
                {
                        while(indx<nchr && *p != '\n')
                        {
                                p++;
                                indx++;
                        }
                        *p =0;

                        write(1, &wbuf, nchr); //test
                        write(1, "assd\n", 5);
                        nchr=0; indx =0;

                        cmp = strcmp(argv[2], wbuf);
                        if(cmp ==0)
                        {
                                found = 1;
                        }
                        else if(cmp < 0)
                        {
                                end = midd;
                        }
                        else if(cmp > 0)
                        {
                                start = midd;
                        }
                }


                if(found == 1)
                {
                        nchr = read(fd, &mbuf, sizeof(mbuf));
                        close(fd);
                        if(nchr == -1)
                        {
                                write(2, "Enable to read\n", 14);
                                exit(-1);
                        }

                        //if nchr == 0 => eof
                         p = mbuf;
                        while(indx<nchr && *p != '\0')
                        {
                                p++;
                                indx++;
                        }
                        *p =0;

                        write(1, &mbuf, nchr);
                        break;
                }
        }
        if(found ==0)
        {
                close(fd);
                write(2, "The word does not exist in the file\n", 36);
                exit(-1);
        }

}

                        
