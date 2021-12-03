#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

int main(int argc, char* argv[])
{

	if (mkfifo("pipe2", 0777) == -1)
	{
		printf("ERROR %i - %s\n", errno, strerror(errno));
		return -1;
	}

	int fd1 = open("./pipe",  O_RDWR | O_NONBLOCK);
	int fd2 = open("pipe2", O_RDWR | O_NONBLOCK);

	if (fd1 == -1 || fd2 == -1)
	{
		printf("ERROR %i - %s\n", errno, strerror(errno));
		close(fd1);
		close(fd2);
		return -1;
	}

	char buf[256];
	int leidos, sel = 0, nfds, n_act, fd_act;

	while(sel != -1)
	{
		fd_set fd_pipes;
		FD_ZERO(&fd_pipes);
		FD_SET(fd1, &fd_pipes);
		FD_SET(fd2, &fd_pipes);

		nfds = fd1+1;
		if(fd1 < fd2)
		{
			nfds = fd2+1;
		}

		sel = select(nfds, NULL, NULL, NULL, NULL);

		if (sel > 0)
		{
			n_act = 0;

			if (FD_ISSET(fd1, &fd_pipes)) 
			{
				n_act = 1;
				fd_act = fd1;
			}
	
			else if (FD_ISSET(fd2, &fd_pipes)) {
				n_act = 2;
				fd_act = fd2;
			}
		}
		
		leidos = 0;
		int long_leidos = read(fd_act, buf, 1);
		while(long_leidos > 0)
		{
			leidos++;
			long_leidos = read(fd_act, buf, 1);
		}

		buf[leidos] = '\0';
		printf("pipe%i: %s", n_act, buf);

		if (long_leidos == 0 && n_act == 1) 
		{
			close(fd1);
			fd1 = open("./pipe", O_RDONLY | O_NONBLOCK);

			if (fd1 == -1) 
			{
				printf("ERROR %i - %s\n", errno, strerror(errno));
				close(fd1);
				close(fd2);
				return -1;
			}
		}

		else if (long_leidos == 0 && n_act == 2) 
		{
			close(fd2);
			fd2 = open("pipe2", O_RDONLY | O_NONBLOCK);

			if (fd2 == -1) 
			{
				printf("ERROR %i - %s\n", errno, strerror(errno));
				close(fd1);
				close(fd2);
				return -1;
			}
		}

	}

	printf("ERROR %i - %s\n", errno, strerror(errno));
	close(fd1);
	close(fd2);
	return -1;
	
}
