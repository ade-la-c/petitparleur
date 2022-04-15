#ifndef COMMON_H
# define COMMON_H

# include <iostream>

# include <sys/socket.h>
# include <netdb.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

# define SERVER_PORT		8000
# define MAXFD				1024

typedef struct sockaddr_in	SA_IN;
typedef struct sockaddr		SA;

void	exit_error( std::string str, int sockfd ) {

	std::cerr << str << std::endl;
	std::cerr << "errno: " << errno << std::endl;
	close(sockfd);
	exit(1);
}

#endif
