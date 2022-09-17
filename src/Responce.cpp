#include "Responce.hpp"

std::string	responce_code(int state)
{
	std::string	content;

	switch (state)
	{
	case BAD_REQUEST_400:
		content =  "<h1>400 Bad Request</h1>";
		break;
	case NOT_FOUND_404:
		content = "<h1>404 Not Found</h1>";
		break;
	case FORBIDDEN_403:
		content = "<h1>403 Forbidden</h1>";
		break;
	case INTERNAL_SERVER_ERROR_500:
		content = "<h1>500 INTERNAL SERVER ERROR</h1>";
		break;
	case OK_200_DEL:
		content = "<h1>Succesfully delete file</h1>";
		break;
	case OK_200_POST:
		content = "<h1>Succesfully post file</h1>";
		break;
	case REQUEST_ENTITY_TOO_LARGE_413:
		content =  "<h1>413 Request Entity Too Large</h1>";
		break;
	case NOT_ALLOWED_405:
		content =  "<h1>413 Method Not Allowed </h1>";
		break;
	default:
		break;
	}
	return content;
}


Responce::Responce():head(""), body(""), responce_code(""),
		content(""), response_(""), www(""), root(""), state(START), code_number(0) {};

void	Responce::start(ServerParam &file, Request& req)
{
	if (check_req(file, req))
	{
		if (req.method == "GET")
		{
			Responce_get(req);
		}
		else if (req.method == "POST")
		{
			Responce_post(req);
		}
		else if (req.method == "DELETE")
		{
			Responce_del(req);
		}
		return;
	}
	else if (req.status == DEFAULT)
	{
		code_number = 405;
		req.status = NOT_ALLOWED_405;
	}
	bad_request(req);	
}

void	Responce::bad_request(Request& req)
{	
	content = ::responce_code(req.status);
	state = READY;	
	make_answer();
}

int	Responce::check_entity(ServerParam &file, Request& req, int i)
{
	int max_body = file.getLocation()[i].getMaxBody();
	if (req.method == "POST")
	{
		if (max_body != -1 && (size_t)max_body <= req.body.size())
		{
			code_number = 413;
			req.status = REQUEST_ENTITY_TOO_LARGE_413;
			return 0;
		}	
	}
	return 1;
}

int	Responce::check_req(ServerParam &file, Request& req)
{
	size_t flag = 0;
	for (size_t i = 0; i < file.getLocation().size(); i++)
	{
		for (size_t j = 0; j < file.getLocation()[i].getMethod().size(); j++)
		{
			std::cout << file.getLocation()[i].getMethod()[j] << "\n\n";	/*TO DO*/
			if (req.method == file.getLocation()[i].getMethod()[j])
			{
				root = file.getLocation()[i].getRoot();
				if (req.method == "GET")
				{
					// if (req.host == file.getLocation()[i].getName())
					// {
					// 	flag = 1;
					// 	return 1;
					// }
					// if (req.path == file.getLocation()[i].getPath())
					// {
					// 	flag = 1;
					// 	return 1;
					// }
					std::cout << "root = " << root << '\n';					/*TO DO*/
					flag = 1;
					return 1;
				}
				else
				{
					std::cout << req.path.substr(0, 7) << '\n';    			/*TO DO*/
					if (check_entity(file, req, i))
					{
						if (req.path.substr(0, 7) == "/common")
						{					
							flag = 1;
							return 1;
						}
						else if (req.path == "/")
						{
							req.path = "/common/file";
							flag = 1;
							return 1;
						}
					}
					else
						return 0;
				}
			}
		}
	}
	return 0;
}

void	Responce::Responce_get(Request& req)
{
	// std::stringstream response; // сюда будет записываться ответ клиенту
	// code_number = 404;
	// content = "<h1>404 Not Found</h1>";
	if (req.path != "" && root != "www")
		www = "www/" + root + "/index.html";
	else
		www = "www/index.html";
	std::cout << "www = " << www << "\n\n";									/*TO DO*/
	std::ifstream f(www.c_str());
	std::cout << www.c_str() << '\n';
	if (f.good() /*|| req.path == "/my_foto.jpg" */)
	{
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		content = str;
		code_number = 200;
	}
	else
	{
		req.status = NOT_FOUND_404;
		content = ::responce_code(req.status);
		code_number = 404;
	}
	state = READY;
	make_answer();
}

void	Responce::Responce_del(Request& req)
{
	www = "www" + root;
	if (std::remove(www.c_str()))
	{
		req.status = BAD_REQUEST_400;
		code_number = 400;
		content = ::responce_code(req.status);
	}
	else
	{
		req.status = OK_200_DEL;
		code_number = 200;
		content = ::responce_code(req.status);
	}		
	state = READY;
	make_answer();
}

void	Responce::Responce_post(Request& req)
{
	std::string file = req.chunked_body + req.body;
	www =  "www" + root;
	std::ofstream out(www.c_str());
	if (out.good())
	{
		out << file;
		req.status = OK_200_POST;
		content = ::responce_code(req.status);
		code_number = 200;
	}
	else
	{
		req.status = NOT_FOUND_404;
		content = ::responce_code(req.status);
		code_number = 404;
	}		
	state = READY;
	make_answer();
}

void	Responce::make_answer()
{
	std::stringstream response;
	response 	<< "HTTP/1.1 " << code_number << "\r\n"
				<< "Version: HTTP/1.1\r\n"
				<< "Content-Type: text/html; charset=utf-8\r\n"
				<< "Accept-Ranges: bytes\r\n"
				<< "Content-Length: " << content.length()
				<< "\r\n\r\n"
				<< content.c_str();
	response_ = response.str();
}

void	Responce::init()
{
	head = "";
	root = "";
	body = "";
	responce_code = "";
	content = "";
	response_ = "";
	www = "";
	state = START;
	code_number = 0;
}