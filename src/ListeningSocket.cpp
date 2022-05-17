#include "ListeningSocket.hpp"

ListeningSocket::ListeningSocket(int port, int backlog_): ASocket(port)
{
	backlog = backlog_;
	int yes = 1;
	setsockopt(get_sock(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	res = bind(get_sock(), (sockaddr *)&get_address(), sizeof get_address());
	start_listening();
	test_connection(listening);
}

ListeningSocket::ListeningSocket() : ASocket(){};

void	ListeningSocket::start_listening()
{
	listening = listen(get_sock(), backlog);
}

ListeningSocket::~ListeningSocket(){};
