#include "Http_server.hpp"
#include "Request.hpp"
#include "Responce.hpp"

// int	Http_server::setServ(Parser_conf &conf)
// {
// 	if (conf.get_servsize())
// 	{
// 		for (size_t i = 0; i < conf.get_servsize(); i++)
// 		{
// 			Server *serv = new Server(conf.getServers()[i].getPort());
// 			server_pull.push_back(serv);
// 			if (serv->setup(backlog))
// 			{
// 				if (mx < serv->getSock())
// 					mx = serv->getSock();
// 				servers.insert(std::make_pair(serv->getSock(), conf.getServers()[i]));
// 			}
// 		}
// 		return 1;
// 	}
// 	return 0;		
// }

int	Http_server::setServ()
{
	std::cout << "line 27\n";
	LocationData* loc = new LocationData();
	loc->setMaxBody(100);
	loc->setMethod("GET");
	loc->setName("Name");
	loc->setPath("/");
	loc->setRoot("www");
	std::vector<LocationData> vec;
	vec.push_back(*loc);
	Server *serv = new Server(8000); 
	ServerParam* sp = new ServerParam(8000, vec);
	if (serv->setup(backlog))
	{
		if (mx < serv->getSock())
			mx = serv->getSock();
		servers.insert(std::make_pair(serv->getSock(), *sp));
	}
	std::cout << "line 44\n";
	return 1;
}

Http_server::Http_server(int backlog, const Parser_conf& conf): clients(), servers(), mx(0), backlog(backlog), conf(conf)
{
	std::cout << "Calling constructor with parametres\n";
	clear();
	clear_set();
	clients.clear();
}

Http_server::Http_server():clients(), servers()
{
	std::cout << "Calling default constructor from  Http_server default\n\n";
	mx = 0;
	backlog = 100;
	clear();
	clear_set();
	clients.clear();
}

void	Http_server::clear_set()
{
	FD_ZERO(&readset);
	FD_ZERO(&writeset);
}

void Http_server::launch()
{
	while (true)
	{
		std::cout << "===========Waiting==========\n";
		int max = mx;
		clear_set();
		std::cout << "line 79\n";
		for (std::map<int, ServerParam>::iterator it = servers.begin(); it != servers.end(); ++it)
			FD_SET(it->first, &readset);
		std::cout << "line 82\n";
		for(std::list<Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			// FD_SET(it->fd, &readset);
			std::cout << "line 86\n";
			if ((*it)->answer.state == CLOSE)
			{
				std::cout << "line 89\n";
				close((*it)->fd);
				delete *it;
				clients.erase(it);
				std::cout << "line 93\n";
			}
			
			else if ((*it)->answer.state == READY)
				{FD_SET((*it)->fd, &writeset);
				std::cout << "line 98\n";}
			else
				{FD_SET((*it)->fd, &readset);
				std::cout << "line 101\n";}
			if ((*it)->fd > max)
				max = (*it)->fd;
			std::cout << "line 104\n";
		}

		/**********************************SELECT****************************************/
		/*********************************************************************************/
		int res = select(max + 1, &readset, &writeset, NULL, NULL);
		std::cout << "-------------------Select-----------------" << std::endl;
		if (res < 0)
			continue;
		std::cout << "line 113\n";
		std::map<int, ServerParam>::iterator it = servers.begin();
		for (; it != servers.end(); ++it)
		{
			std::cout << "line 117\n";
			if (FD_ISSET(it->first, &readset))
			{
				// Поступил новый запрос на соединение, используем accept
				std::cout << "line 121\n";
				new_socket = accept(it->first, NULL, NULL);
				if (new_socket < 0)
				{
					perror("accept");
					return;
				}
				fcntl(new_socket, F_SETFL, O_NONBLOCK);
				Client *cl = new Client(it->first, new_socket, it->second);	
				clients.push_back(cl);
				std::cout << "line 131\n";
			}
		}
		for(std::list<Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			std::cout << "line 136\n";
			if(FD_ISSET((*it)->fd, &readset))
			{
				// Поступили данные от клиента, читаем их
				std::cout << "line 140\n";
				int bytes_read = recv((*it)->fd, (*it)->accept, 1024, 0);
				(*it)->accept[bytes_read] = '\0';
				std::cout << "fd = " << (*it)->fd << " , bytes = " << bytes_read << std::endl;
				std::string temp = (*it)->accept;
				std::cout << "Reading = " << temp << std::endl << std::endl;
				temp = "";
				if (bytes_read <= 0)
				{
					(*it)->answer.state = CLOSE;
					std::cout << "line 150\n";
					// Соединение разорвано, удаляем сокет из множества
					// close((*it)->fd);
					// delete *it;
					// clients.erase(it);
					// continue;
				}
				std::cout << "line 157\n";
				(*it)->recieve_req((*it)->accept);
				(*it)->init();
				(*it)->req.state = CLIENT_START;
				(*it)->req.recieve((*it)->arr, (*it)->buffer);
				std::cout << "line 162\n";
				if ((*it)->req.state == CLIENT_RECEIVE_REQUEST)
				{
					std::cout << "line 165\n";
					(*it)->answer.start((*it)->param, (*it)->req);
					(*it)->req.sendto = "";
					std::cout << "Responce = " << (*it)->answer.response_ << "\n\n";
				}
			}
			std::cout << "line 171\n";
			if(FD_ISSET((*it)->fd, &writeset))
			{
				std::cout << "line 174\n";
				size_t result = send((*it)->fd, (*it)->answer.response_.c_str(),
							(*it)->answer.response_.length(), 0);
				std::cout << "line 177\n";
				if (result < 0)
				{
					// произошла ошибка при отправле данных
					std::cerr << "send failed: " << "\n";
				}
				std::cout << "line 183\n";
				if (result >= (*it)->answer.response_.length())
				{
					(*it)->answer.state = DONE;
					std::cout << "req.Connection = "  << (*it)->req.Connection << '\n';
					if ((*it)->req.Connection == "close")
					{
						(*it)->answer.state = CLOSE;
						std::cout << "line 191\n";
						// close((*it)->fd);
						// delete *it;
						// clients.erase(it);
					}
					std::cout << "line 196\n";
					(*it)->req.init();
					(*it)->answer.init();
					std::cout << "line 199\n";
				}
				else
				{
					(*it)->answer.response_.substr(result);
					(*it)->req.init();
					std::cout << "line 205\n";
				}
			}
		}
		std::cout << "============Done============\n\n";
	}
}

Http_server::~Http_server()
{
	std::cout << "Calling destructor from Http_server\n\n";
	for (size_t i = 0; i < server_pull.size(); i++)
	{
		delete server_pull[i];
	}
}

void Http_server::clear()
{
	for (size_t i = 0; i < 1024; i++)
		arr[i] = '\0';
}
