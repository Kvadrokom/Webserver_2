#include "ASocket.hpp"
#include "BindingSocket.hpp"
#include "ListeningSocket.hpp"
#include "Http_server.hpp"

int	main()
{
	std::cout << "Starting...\n";
	std::cout << "Binding socket...\n";
	BindingSocket bs(AF_INET, SOCK_STREAM, 0, 8500, INADDR_ANY);
	std::cout << "Listening Socket...\n";
	ListeningSocket ls(AF_INET, SOCK_STREAM, 0, 7500, INADDR_ANY, 10);
	std::cout << "Succes\n";
	return 0;
}