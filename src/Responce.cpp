#include "Responce.hpp"

Responce::Responce():head(""), body(""), responce_code(""),
		content(""), response_("") {};

void	Responce::start(ServerParam &file, Request& req)
{
	if (check_req(file, req))
	{
		if (req.method ==  "GET")
		{
			Responce_get(req);
		}
		else if (req.method ==  "POST")
		{
			Responce_post(req);
		}
		else if (req.method ==  "DELETE")
		{
			Responce_del(req);
		}
	}
	else
		bad_request();
}

void	Responce::bad_request()
{
	req.status = BAD_REQUEST_400;
}

int	Responce::check_req(ServerParam &file, const Request& req)
{
	size_t flag = 0;
	for (size_t i = 0; i < file.getLocation().size(); i++)
	{
		if (req.method == file.getLocation()[i].getMethod())
		{
			if (req.path == file.getLocation()[i].getPath())
			{
				flag = 1;
				return 1;
			}
		}
	}
	return 0;
}

void	Responce::Responce_get(Request& req)
{
	std::stringstream response;		 // сюда будет записываться ответ клиенту
	// std::stringstream response_body; 
	int errorCode = 404;
	// std::string htmlFile = req.path;
	std::string content = "<h1>404 Not Found</h1>";
	std::string www = "www" + req.path + "index.html";
	std::ifstream f(www.c_str());
	std::cout << www.c_str() << '\n';
	if (f.good() /*|| req.path == "/my_foto.jpg" */)
	{
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		content = str;
		errorCode = 200;
	}
	// response_body << content;
	response 	<< "HTTP/1.1 " << errorCode << "\r\n"
				<< "Version: HTTP/1.1\r\n"
				<< "Content-Type: text/html; charset=utf-8\r\n"
				<< "Accept-Ranges: bytes\r\n"
				<< "Content-Length: " << content.length()
				<< "\r\n\r\n"
				<< content.c_str();
	response_ = response.str();
}

void	Responce::Responce_del(Request& req)
{
	std::string www = "www" + req.path;
	if (std::remove(www.c_str()))
	{
		req.status = NOT_FOUND_404;
	}
	else
		req.status = OK_200;
}

void	Responce::Responce_post(Request& req)
{
	std::string file = req.chunked_body + req.body;
	std::ofstream out("file1.txt");
	out << file;
	// req.status = NOT_FOUND_404;
}