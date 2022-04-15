#include "common.h"

int		setup_server( int port, int backlog ) {

	int		servsocket, clientsocket, addrsize;
	SA_IN	servaddr;

	if ((servsocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		exit_error("socket failed.", servsocket);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(port);

	if (bind(servsocket, (SA *)&servaddr, sizeof(servaddr)) == -1)
		exit_error("bind failed.", servsocket);

	if (listen(servsocket, backlog) == -1)
		exit_error("listen failed.", servsocket);

	return servsocket;
}

int		accept_new_connection( int server_socket ) {

	int		client_socket = accept(server_socket, (SA *) NULL, NULL);

	if (client_socket == -1)
		exit_error("accept failed.", server_socket);
	return client_socket;
}

void	handle_connection( int client_socket ) {

	int			recvstatus;
	char		buf[100];
	ssize_t		buflen = 100;

	recvstatus = recv(client_socket, buf, buflen, 0);
	if (recvstatus == -1) {
		exit_error("recv failed.", client_socket);
	} else if (!recvstatus) {
		std::cout << "client has closed connection" << std::endl;
		return;
	} else {
		std::cout << "msg : " << buf << std::endl;
		bzero(buf, sizeof(buf));
	}
}

int		main( void ) {

	int					servsocket = setup_server(SERVER_PORT, 100);
	fd_set				current_sockets, ready_sockets;

	FD_ZERO(&current_sockets);
	FD_SET(servsocket, &current_sockets);

	while (true) {

		ready_sockets = current_sockets;

		if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
			exit_error("select failed.", -1);

		for (int i = 0; i < FD_SETSIZE; i++) {

			if (FD_ISSET(i, &ready_sockets)) {
				if (i == servsocket) {
					int	clientsocket = accept_new_connection(servsocket);
					FD_SET(clientsocket, &current_sockets);
				} else {
					handle_connection(i);
					FD_CLR(i, &current_sockets);
				}
			}
		}
	}

	return 0;
}
