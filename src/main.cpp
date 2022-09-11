#include "Http_server.hpp"
#include "Parser_conf.hpp"

int	main()
{
	Parser_conf conf("config.conf");
	for (size_t i = 0; i < conf.get_servsize(); i++)
	{
		std::cout << conf.getServers()[i].getPort() << "\n";
		for (size_t j = 0; j < conf.getServers()[i].getLocation().size(); j++)
		{
			std::cout << "Location " << j + 1 << '\n';
			// std::cout << "Method = " << conf.getServers()[i].getLocation()[j].getMethod() << " ";
			std::cout << "Path = " << conf.getServers()[i].getLocation()[j].getPath() << " ";
			std::cout << "Root = " << conf.getServers()[i].getLocation()[j].getRoot() << " ";
			std::cout << "Server_name = " << conf.getServers()[i].getLocation()[j].getName() << " ";
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	
	Http_server server(100, conf);
	if (server.setServ(conf))
		server.launch();
	return 0;
}