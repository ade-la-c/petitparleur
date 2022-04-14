#include "common.h"

int		main( void ) {

	int		sockfd;

	struct sockaddr_in	addr;
	socklen_t			addrlen = sizeof(sockaddr_in);

	bzero(&addr, sizeof(addr));
	addr.sin_family			= AF_INET;
	addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	addr.sin_port			= htons(SERVER_PORT);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	connect(sockfd, (sockaddr *)&addr, addrlen);

	while (true) {

		std::string		str;

		// std::cin >> str;

		std::getline(std::cin, str);

		// std::cout << "str : " << str << std::endl;

		if (send(sockfd, str.c_str(), str.length(), 0) < 0) {
			exit_error("send failed.", sockfd);
		} else if (str == "end")
			break;
		else
			std::cout << "message sended" << std::endl;
	}
	return 0;
}
