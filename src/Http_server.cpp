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
	return 1;
}

Http_server::Http_server(int backlog, const Parser_conf& conf): mx(0), backlog(backlog), conf(conf)
{	
	clear();
	clear_set();
	clients.clear();
}

Http_server::Http_server()
{
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
		for (std::map<int, ServerParam>::iterator it = servers.begin(); it != servers.end(); ++it)
			FD_SET(it->first, &readset);
		for(std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			// FD_SET(it->fd, &readset);
			if (it->answer.state == READY)
				FD_SET(it->fd, &writeset);
			else
				FD_SET(it->fd, &readset);
			if (it->fd > max)
				max = it->fd;
		}

		/**********************************SELECT****************************************/
		/*********************************************************************************/
		int res = select(max + 1, &readset, &writeset, NULL, NULL);
		std::cout << "-------------------Select-----------------" << std::endl;
		if (res < 0)
			continue;
		std::map<int, ServerParam>::iterator it = servers.begin();
		for (; it != servers.end(); ++it)
		{
			if (FD_ISSET(it->first, &readset))
			{
				// Поступил новый запрос на соединение, используем accept
				new_socket = accept(it->first, NULL, NULL);
				if (new_socket < 0)
				{
					perror("accept");
					return;
				}
				fcntl(new_socket, F_SETFL, O_NONBLOCK);
				Client *cl = new Client(it->first, new_socket, it->second);
				clients.push_back(*cl);
			}
		}
		for(std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if(FD_ISSET(it->fd, &readset))
			{
				// Поступили данные от клиента, читаем их
				int bytes_read = recv(it->fd, it->accept, 1024, 0);
				it->accept[bytes_read] = '\0';
				std::cout << "fd = " << it->fd << " , bytes = " << bytes_read << std::endl;
				std::string temp = it->accept;
				std::cout << "Reading = " << temp << std::endl << std::endl;
				temp = "";
				if (bytes_read <= 0)
				{
					// Соединение разорвано, удаляем сокет из множества
					close(it->fd);
					clients.erase(it);
					continue;
				}
				it->recieve_req(it->accept);
				it->init();
				it->req.state = CLIENT_START;
				it->req.recieve(it->arr, it->buffer);
				if (it->req.state == CLIENT_RECEIVE_REQUEST)
				{
					it->answer.start(it->param, it->req);
					it->req.sendto = "";
					std::cout << "Responce = " << it->answer.response_ << "\n\n";
				}
			}
			if(FD_ISSET(it->fd, &writeset))
			{
				size_t result = send(it->fd, it->answer.response_.c_str(),
							it->answer.response_.length(), 0);
				if (result < 0)
				{
					// произошла ошибка при отправле данных
					std::cerr << "send failed: " << "\n";
				}
				if (result >= it->answer.response_.length())
				{
					it->answer.state = DONE;
					std::cout << "req.Connection = "  << it->req.Connection << '\n';
					if (it->req.Connection == "close")
					{
						close(it->fd);
						clients.erase(it);
					}
					it->req.init();
					it->answer.init();
				}
				else
				{
					it->answer.response_.substr(result);
					it->req.init();
				}
			}
		}
		std::cout << "============Done============\n\n";
	}
}

Http_server::~Http_server()
{
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
