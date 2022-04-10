#ifndef ASERVER_H
#define ASERVER_H

#include "ListeningSocket.hpp"

class AServer
{
private:
	ListeningSocket *listen_socket;
	virtual void accepter() = 0;
	virtual void handler(int fd) = 0;
	void virtual responder(int fd, std::string content, int errorCode) = 0;


public:
	AServer(int domain, int service, int protocol, int port,
				u_long interface, int backlog);
	virtual~AServer();

	virtual void launch() = 0;

	ListeningSocket *getsocket();
};

#endif