#include "BindingSocket.hpp"

BindingSocket::BindingSocket(int domain, int service, int protocol, int port,
	u_long interface): ASocket(domain, service, protocol, port, interface)
{
	int yes = 1;
	setsockopt(get_sock(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	set_connection(connect_to_network(get_sock(), get_address()));
	test_connection(get_connection());
}

BindingSocket::BindingSocket(){};

int BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	int fd = bind(sock, (sockaddr *)&address, sizeof address);
	return fd;
}

BindingSocket::~BindingSocket(){};

void	BindingSocket::set_connection(int connect){connection = connect;}

int	BindingSocket::get_connection(){return connection;}