#ifndef LSOCKET_H
#define LSOCKET_H

#include "BindingSocket.hpp"

class ListeningSocket: public BindingSocket
{
private:
	int backlog;
	int listening;

public:
	ListeningSocket(int domain, int service, int protocol, int port,
				u_long interface, int backlog_);
	void	start_listening();
	~ListeningSocket();
};




#endif