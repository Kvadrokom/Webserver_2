#include "Http_server.hpp"
#include "Request.hpp"
#include "Responce.hpp"

int	Http_server::setServ(Parser_conf &conf)
{
	if (conf.get_servsize())
	{
		for (size_t i = 0; i < conf.get_servsize(); i++)
		{
			Server *serv = new Server(conf.getServers()[i].getPort());
			server_pull.push_back(serv);
			if (serv->setup(backlog))
			{
				// FD_SET(serv->getSock(), &masterset);
				if (mx < serv->getSock())
					mx = serv->getSock();
				servers.insert(std::make_pair(serv->getSock(), conf.getServers()[i]));
			}
		}
		return 1;
	}
	return 0;		
}

Http_server::Http_server(int backlog, const Parser_conf& conf): mx(0), backlog(backlog), conf(conf)
{	
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
			FD_SET(it->fd, &readset);
			if (it->answer.state == READY)
				FD_SET(it->fd, &writeset);
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
				clients.push_back(Client(it->first, new_socket, it->second));
			}
		}
		for(std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if(FD_ISSET(it->fd, &readset))
			{
				// Поступили данные от клиента, читаем их
				int bytes_read = recv(it->fd, it->accept, 1024, 0);
				std::cout << "fd = " << it->fd << " , bytes = " << bytes_read << std::endl;
				if (bytes_read <= 0)
				{
					// Соединение разорвано, удаляем сокет из множества
					close(it->fd);
					clients.erase(it);
					continue;
				}
				it->recieve_req();
				it->req.state = CLIENT_START;
				it->req.recieve(it->arr, it->accept);
				if (it->req.state == CLIENT_RECEIVE_REQUEST)
				{
					it->answer.start(it->param, it->req);
					std::cout << it->answer.response_;
					std::cout <<"ReqBody = " << it->req.body << "\n";
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
				}
					
				else
				{
					it->answer.response_.substr(result);
					it->req.init();
				}
				if (it->answer.state == DONE && it->req.Connection != "keep-alive")
				{
					close(it->fd);
					clients.erase(it);
				}
			}
		}
		std::cout << "============Done============\n\n";
	}
}

// void Http_server::handler(int fd)
// {
// 	ServerParam src;
// 	int flag = 0;
// 	// std::string www;

// 	for (std::list<Client>::iterator itcl = clients.begin(); itcl != clients.end(); itcl++)
// 	{
// 		if (fd == itcl->fd)
// 		{
// 			std::map<int, ServerParam>::iterator itsv = servers.begin();
// 			for (; itsv != servers.end(); ++itsv)
// 			{
// 				if (itcl->sock == itsv->first)
// 				{
// 					src = itsv->second;
// 					break;
// 				}
// 			}
// 		}	
// 	}	
// 	std::cout << arr << "\n";
// 	std::istringstream iss(arr);
// 	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)),
// 									std::istream_iterator<std::string>());
// 	// Some defaults for output to the client (404 file not found 'page')
// 	std::string content = "<h1>404 Not Found</h1>";
// 	std::string htmlFile = "/index.html";
// 	int errorCode = 404;
	
// 	// If the GET request is valid, try and get the name
// 	if (parsed.size() >= 3)
// 	{
// 		if (parsed[0] == "GET")
// 		{
// 			htmlFile = parsed[1];
// 			for (size_t i = 0; i < src.getLocation().size(); i++)
// 			{
// 				if (htmlFile == src.getLocation()[i].getPath())
// 				{
// 					if (htmlFile == "/")
// 						htmlFile = "/index.html";
// 					else
// 						htmlFile = src.getLocation()[i].getPath() + "/index.html";
// 					flag = 1;
// 					break;
// 				}
// 			}	
// 		}
// 		else if (parsed[0] == "POST")
// 		{
// 			htmlFile = parsed[1];
// 			if (htmlFile == "/")
// 				htmlFile = "/index.html";
// 		}
// 	}
// 	// Open the document in the local file system
// 	std::string www = "www" + htmlFile;
// 	std::ifstream f(www.c_str());

// 	// Check if it opened and if it did, grab the entire contents
// 	if ((f.good() && flag )|| htmlFile == "/my_foto.jpg")
// 	{
// 		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
// 		content = str;
// 		errorCode = 200;
// 	}
// 	f.close();
// 	responder(fd, content, errorCode);
// }



// void Http_server::responder(int fd, std::string content, int errorCode)
// {
// 	std::stringstream response;		 // сюда будет записываться ответ клиенту
// 	std::stringstream response_body; // тело ответа
// 	response_body << content;

// 	// Формируем весь ответ вместе с заголовками
//     response 	<< "HTTP/1.1 " << errorCode << "\r\n"
// 				<< "Version: HTTP/1.1\r\n"
// 				<< "Content-Type: text/html; charset=utf-8\r\n"
// 				<< "Accept-Ranges: bytes\r\n"
// 				<< "Content-Length: " << response_body.str().length()
// 				<< "\r\n\r\n"
// 				<< response_body.str();
// 	int result = send(fd, response.str().c_str(),
// 	response.str().length(), 0);
// 	std::cout << "result = " << result << "\n";
// 	std::cout << response.str().c_str() << "\n";
// 	clear();
// 	if (result < 0)
// 	{
// 		// произошла ошибка при отправке данных
// 		std::cerr << "send failed: " << "\n";
// 	}
// }

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
