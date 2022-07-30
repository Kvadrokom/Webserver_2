#include "Request.hpp"

Request::Request(): arr() { init(); }

void	Request::recieve(std::vector<std::string>& arr, std::string& str)
{
	static int count;
	sendto += str;
	this->arr = arr;
	this->buf = str;
	size_t pos;

	std::cout << "sendto = " << sendto << "\nreq_status = " << req_status << "\n\n";

	if ((pos = sendto.find(CRLF_CRLF)) != std::string::npos)
	{
		count++;
		if (req_status == HEADER)
		{
	 		req_status = BODY;
			header = sendto.substr(0, pos + 4);
			std::cout << "Header = " << header << "\nreq_status = " << req_status << "\n";
			parse_header();
		}
		if (req_status == BODY && method == "POST")
			parse_body();
	}
	std::cout << "count = " << count << "\n";
}

void	Request::parse_header()
{
	ft_toupper((method = arr[0]));
	ft_toupper((path = arr[1]));
	ft_toupper(arr[2]);
	
	std::istringstream iss(header.c_str());
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)),
									std::istream_iterator<std::string>());
	ft_toupper((method = parsed[0]));
	ft_toupper((path = parsed[1]));
	ft_toupper(parsed[2]);
	if (parsed[2] != "HTTP/1.1" || allowed_req(method))
	{
		state = CLIENT_RECEIVE_REQUEST;
		status = BAD_REQUEST_400;
		return;
	}
	for (size_t i = 0; i < parsed.size(); ++i)
	{
		if (parsed[i] == "server_name:")
			Server_name = parsed[i + 1];
		if (parsed[i] == "Connection:")
			Connection = parsed[i + 1];
		if (parsed[i] == "Content-Length:")
			Content_Length = std::atoi(parsed[i + 1].c_str());
		if (parsed[i] == "Transfer-Encoding:")
		{
			Transfer_Encoding = parsed[i + 1];
			Content_Length = 0;
		}	
	}
	if (method == "GET" || method == "DELETE")
		state = CLIENT_RECEIVE_REQUEST;
}

Request::~Request(){}

void	Request::parse_body()
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
	req_status = HEADER;
	status = DEFAULT;
	state = CLIENT_DEFAULT;
	Server_name = "";
}

void	Request::get_body_chunked()
{
	std::string chunk_raw;
	if (sendto.size() <= header.size())
		return;
	chunk_raw = sendto.substr(header.size());
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

