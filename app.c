#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

#define PORT 9999

int
main(int argc, char **argv)
{
	int server;
	struct sockaddr_in addr;
	int sd;

	 server = socket(AF_INET, SOCK_STREAM, 0);
	 if (socket < 0)
		 error (1, errno, "socket");

	 memset( &addr, 0, sizeof(addr) );
	 addr.sin_family = AF_INET;
	 addr.sin_addr.s_addr = htonl( INADDR_ANY );
	 addr.sin_port = htons( PORT );
	 
	 if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		 error (1, errno, "bind");

	 if (listen(server, 2) < 0)
		 error (1, errno, "listen");

next:
	 sd = accept(server, NULL, 0);
	 if (sd < 0)
		 error (1, errno, "accept");

	 pid_t pid1 = fork();
	 if (pid1 < 0)
		 error (1, errno, "fork(1)");

	 if (pid1 > 0) 
	 {
		 close (sd);
		 wait(NULL);
		 goto next;
	 }

	 pid_t pid2 = fork();
	 if (pid2 < 0)
		 error (1, errno, "fork(2)");
	 if (pid2 > 0)
		 exit(0);
	 
	 const char msg[] = "hello, world\n";
	 write (sd, msg, sizeof(msg) - 1);
	 shutdown(sd, SHUT_RDWR);
	 exit(0);
}
