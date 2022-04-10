#include "ListeningSocket.hpp"

ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port,
				u_long interface, int backlog_): BindingSocket(domain, service, protocol,
				port, interface)
{
	backlog = backlog_;
	start_listening();
	test_connection(listening);
}

void	ListeningSocket::start_listening()
{
	listening = listen(get_sock(), backlog);
}

ListeningSocket::~ListeningSocket(){};
