#include "Http_server.hpp"

int	Http_server::setServ(Parser_conf &conf)
{
	for (size_t i = 0; i < conf.get_servsize(); i++)
	{
		Server *serv = new Server(conf.getServers()[i].getPort());
		if (serv->setup() && serv->make_nonblocking(serv->getSock()))
		{
			FD_SET(serv->getSock(), &masterset);
			if (mx < serv->getSock())
				mx = serv->getSock();
			servers.insert(std::make_pair(serv->getSock(), *conf.getServers()));
		}
		else
			return 0;
	}
	return 1;
}

Http_server::Http_server(): mx(0)
{	
	clear();
	FD_ZERO(&masterset);
	FD_ZERO(&readset);
	FD_ZERO(&writeset);
	// fcntl(sock_sv, F_SETFL, O_NONBLOCK);
	// timeout.tv_sec = 15;
	// timeout.tv_usec = 0;
	clients.clear();
	// FD_ZERO(&readset);
	// clients.insert(sock_sv);
	// mx = sock_sv;
	// launch();
}


void Http_server::launch()
{
	while (true)
	{
		std::cout << "===========Waiting==========\n";
		readset = masterset;
		if (select(mx + 1, &readset, &writeset, NULL, NULL) <= 0)
			continue;
		std::map<int, ServerParam>::iterator it = servers.begin();
		for (; it != servers.end(); ++it)
		{
			if(FD_ISSET(it->first, &readset))
			{
				// Поступил новый запрос на соединение, используем accept
				new_socket = accept(it->first, NULL, NULL);
				if (new_socket < 0)
				{
					perror("accept");
					return;
				}
				if (new_socket > mx)
					mx = new_socket;
				fcntl(new_socket, F_SETFL, O_NONBLOCK);
				clients.insert(new_socket);
				FD_SET(new_socket, &masterset);
			}
		}
		for(std::set<int>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if(FD_ISSET(*it, &readset))
			{
				// Поступили данные от клиента, читаем их
				int bytes_read = recv(*it, arr, 1024, 0);
				std::cout << "fd = " << *it << " , bytes = " << bytes_read << std::endl;
				if (bytes_read <= 0 && *it != sock_sv)
				{
					// Соединение разорвано, удаляем сокет из множества
					close(*it);
					clients.erase(*it);
					FD_CLR(*it, &readset);
					continue;
				}
				if (*it != sock_sv)
				{
					handler(*it);
					// responder(*it);
				}
			}
		}
		
		// for(std::set<int>::iterator it = clients.begin(); it != clients.end(); it++)
		// 	FD_SET(*it, &readset);
		// mx = std::max(mx, *std::max_element(clients.begin(), clients.end()));
		// if(select(mx + 1, &readset, NULL, NULL, NULL) <= 0)
		// {
		// 	perror("select");
		// 	continue;;
		// }
		// accepter();
		std::cout << "============Done============\n\n";
		
	}
}

void Http_server::accepter()
{
	if(FD_ISSET(sock_sv, &readset))
	{
		// Поступил новый запрос на соединение, используем accept
		new_socket = accept(sock_sv, NULL, NULL);
		if(new_socket < 0)
		{
			perror("accept");
			return;
		}
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
		clients.insert(new_socket);
		// FD_SET(new_socket, &readset);
	}
	for(std::set<int>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if(FD_ISSET(*it, &readset))
		{
			// Поступили данные от клиента, читаем их
			int bytes_read = recv(*it, arr, 1024, 0);
			std::cout << "fd = " << *it << " , bytes = " << bytes_read << std::endl;
			if (bytes_read <= 0 && *it != sock_sv)
			{
				// Соединение разорвано, удаляем сокет из множества
				close(*it);
				clients.erase(*it);
				FD_CLR(*it, &readset);
				continue;
			}
			if (*it != sock_sv)
			{
				handler(*it);
				// responder(*it);
			}
		}
	}
}

void Http_server::handler(int fd)
{
	std::cout << arr << "\n";
	std::istringstream iss(arr);
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)),
									std::istream_iterator<std::string>());
	// Some defaults for output to the client (404 file not found 'page')
	std::string content = "<h1>404 Not Found</h1>";
	std::string htmlFile = "/index.html";
	int errorCode = 404;

	// If the GET request is valid, try and get the name
	if (parsed.size() >= 3)
	{
		if (parsed[0] == "GET")
		{
			htmlFile = parsed[1];
			// If the file is just a slash, use index.html. This should really
			// be if it _ends_ in a slash. I'll leave that for you :)
			if (htmlFile == "/")
			htmlFile = "/index.html";
		}
		else if (parsed[0] == "POST")
		{
			htmlFile = parsed[1];
			if (htmlFile == "/")
			htmlFile = "/index.html";
		}
	}
	// Open the document in the local file system
	std::string www = "www" + htmlFile;
	std::ifstream f(www.c_str());

	// Check if it opened and if it did, grab the entire contents
	if (f.good())
	{
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		content = str;
		errorCode = 200;
	}
	f.close();
	responder(fd, content, errorCode);
}

void Http_server::responder(int fd, std::string content, int errorCode)
{
	std::stringstream response;		 // сюда будет записываться ответ клиенту
	std::stringstream response_body; // тело ответа
	response_body << content;

	// Формируем весь ответ вместе с заголовками
    response 	<< "HTTP/1.1 " << errorCode << "\r\n"
				<< "Version: HTTP/1.1\r\n"
				<< "Content-Type: text/html; charset=utf-8\r\n"
				<< "Accept-Ranges: bytes\r\n"
				<< "Content-Length: " << response_body.str().length()
				<< "\r\n\r\n"
				<< response_body.str();
	int result = send(fd, response.str().c_str(),
	response.str().length(), 0);
	std::cout << "result = " << result << "\n";
	std::cout << response.str().c_str() << "\n";
	clear();
	if (result < 0)
	{
		// произошла ошибка при отправле данных
		std::cerr << "send failed: " << "\n";
	}
}

Http_server::~Http_server(){};

void Http_server::clear()
{
	for (size_t i = 0; i < 1024; i++)
		arr[i] = '\0';
}

// <!DOCTYPE html>
// <html>
//  <head>
//   <meta charset="utf-8">
//   <title>ООО Василий Пупкин</title>
//  </head>
//  <body>
//   <h1>Информация о нашей компании</h1>
// 	<center><img src="we.jpg" width="30%" /></center>
//     <h2>Кто мы?</h2>
// 	<p>Мы - комманда профессионалов.</p>
//     <h2>Наши услуги</h2>
// 	<h3>Создание сайтов</h3>
// 	  <p>Мы создаем по-настоящему крутые сайты.</p>
// 	<h3>Продвижение сайтов</h3>
// 	  <p>Ваш сайт в ТОП-3 поисковых систем через 2 дня.</p>
// 	<h3>Посадка картошки</h3>
// 	  <p>20 соток в час.</p>
//      <h2>Контакты</h2>
// 	<div id="map">Карта проезда: 
// 	   ...	
// 	</div>
// 	<p>Телефон: 0000</p>
//  </body>
// </html>
// Основ