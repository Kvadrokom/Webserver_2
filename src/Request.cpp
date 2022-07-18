#include "Request.hpp"

Request::Request(): arr() { init(); }

void	Request::recieve(std::vector<std::string> arr, std::string str)
{
	sendto += str;
	this->arr = arr;
	this->buf = str;
	size_t pos;

	if ((pos = str.find(CRLF_CRLF)) != std::string::npos)
	{
	 	if (req_status == DEF_REQ)
	 	{
	 		req_status = HEADER;
			header = sendto.substr(0, pos + 4 );
			std::cout << header << "\n";
			parse_header();
		}
		else
			parse_body();
	}
	if (Content_Length && Content_Length >= (int)(sendto.size() - header.size()))
	{
		state = CLIENT_RECEIVE_REQUEST;
		parse_body();
	} 	
	else if (req_status !=  HEADER && (method == "GET" || method == "DELETE"))
		state = CLIENT_RECEIVE_REQUEST;
	else if (Transfer_Encoding == "chunked")
		get_body_chunked();
	// this->start();
	// Request::parse_header();
}

void	Request::parse_header()
{
	ft_toupper((method = arr[0]));
	ft_toupper((path = arr[1]));
	ft_toupper(arr[2]);
	if (arr[2] != "HTTP/1.1" || allowed_req(arr[0]))
	{
		state = CLIENT_TERMINATED;
		status = BAD_REQUEST_400;
		return;
	}
	size_t pos = buf.find(CRLF_CRLF);
	if (pos != std::string::npos)
	{
		req_status = BODY;
		for (size_t i = 0; i < pos; ++i)
		{
			if (arr[i] == "Connection:")
				Connection = arr[i + 1];
			if (arr[i] == "Content-Length:")
				Content_Length = std::atoi(arr[i + 1].c_str());
			if (arr[i] == "Transfer-Encoding:")
			{
				Transfer_Encoding = arr[i + 1];
				Content_Length = 0;
			}	
		}
	}
}

Request::~Request(){}

void	Request::parse_body()
{
	start();
}

void	Request::start()
{
	if (Transfer_Encoding == "chunked")
		get_body_chunked();
	else if (Content_Length)
		get_body_length();
	else
	{
		state = CLIENT_TERMINATED;
		status = BAD_REQUEST_400;
		return;
	}
}

void	Request::init()
{
	Content_Length = 0;
	Transfer_Encoding = "";
	Connection = "";
	method = "";
	buf = "";
	sendto = "";
	chunked_body = "";
	req_status = DEF_REQ;
	status = DEFAULT;
	state = CLIENT_DEFAULT;
}

void	Request::get_body_chunked()
{
	std::string chunk_raw;
	chunk_raw = buf.substr(header.size());
	size_t size = atoi(chunk_raw.c_str());
	if (size == 0)
	{
		req_status = END_REQ;
		state = CLIENT_RECEIVE_REQUEST;
	}
	size_t pos;
	if ((pos = chunk_raw.find(CRLF)) != std::string::npos)
		chunked_body += chunk_raw.substr(pos + 2, size);
	// std::cout << "chunked_body = " << chunked_body << '\n';
}

void	Request::get_body_length()
{
	// std::cout << sendto << '\n';
	// std::cout << "sendto.size() = " << sendto.size() << ' ' << "header.size() = " << header.size() << '\n';
	if (req_status == BODY)
	{
		if (sendto.size() - header.size() >= (unsigned long)Content_Length)
		{
			req_status = END_REQ;
			state = CLIENT_RECEIVE_REQUEST;
			body = sendto.substr(header.size(), Content_Length);
		}
	}
	else
		req_status = BODY;
}


void	ft_toupper(std::string& str)
{
	for (size_t i = 0; i < str.size(); i++)
		toupper(str.c_str()[i]);
}

int		allowed_req(std::string& str)
{
	ft_toupper(str);

	if (str != "GET" || str != "POST" || str != "DELETE")
		return 0;
	return 1;
}

