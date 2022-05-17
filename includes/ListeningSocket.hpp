#ifndef LSOCKET_H
#define LSOCKET_H

#include "BindingSocket.hpp"

class ListeningSocket: public ASocket
{
private:
	int backlog;
	int listening;
	int res;

public:
	ListeningSocket(int port, int backlog_);
	ListeningSocket();
	void	start_listening();
	~ListeningSocket();
};




#endif