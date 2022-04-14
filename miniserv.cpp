#include "common.h"

int		main() {

	int					listenfd, connfd;
	struct sockaddr_in	servaddr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		exit_error("socket error.", listenfd);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family			= AF_INET;
	servaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	servaddr.sin_port			= htons(SERVER_PORT);

	if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		exit_error("bind error.", listenfd);

	if ((listen(listenfd, 10)) < 0)
		exit_error("listen error.", listenfd);

	while (true) {

		struct sockaddr_in	addr;
		socklen_t			addr_len;
		char				buf[100];
		ssize_t				buflen = 100;

		std::cout << "waiting for a connection on port " << SERVER_PORT << std::endl;
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

		int		recvstatus;

		while ((recvstatus = recv(connfd, buf, buflen, 0)) != -1) {
			if (!recvstatus) {
				std::cout << "client has closed connection" << std::endl;
				bzero(buf, sizeof(buf));
				break;
			}
			std::cout << "msg : " << buf << std::endl;
			bzero(buf, sizeof(buf));
		}
	}
	return 0;
}
