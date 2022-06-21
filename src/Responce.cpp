#include "Responce.hpp"

void	Responce::heading(const int content_size, const std::string &file)
{
	head = "HTTP/1.1 200 OK\r\n";	
	std::string Content_Type, Content_Length;
	std::string extension = file.substr(file.find(".") + 1);	
	if (extension == "png" || extension == "gif")
		Content_Type = "Content-Type: image/apng\r\n";
	else if(extension == "jpg")
		Content_Type = "Content-Type: image/jpeg\r\n";
	else
		Content_Type = "Content-Type: text/html\r\n";
	Content_Length = "Content-Lenght: " + std::to_string(content_size) + "\r\n";
	head = head + "Server: Cone \r\n" + Content_Type + Content_Length + "Connection: keep-alive\r\n\r\n";
}

void	Responce::static_handle()
{
	std::string buffer; // создаем буфер в который будем формировать сообщение, отправляемое браузеру
	std::ifstream file(getenv("path") + parser->get_file(), std::ifstream::binary); // открываем читаемый файл c конца, скливая переменную окружения "путь" и имя файла
	if (file) // если файл открылся, продолжаем
	 {
		 auto const size{file.tellg()}; //узнаем позицию курсора
		 file.seekg(0); //обнуляем позицию курсора
		 char current;
		 buffer.reserve(size);
		 while(file.get(current)) //читаем файл
			buffer.push_back(current);
		 heading(buffer.length(), parser->get_file()); // этот класс формирует заголовок
		 buffer = head.get_head() + buffer; // приклеиваем полученный заголовок к буферу
		 send(newclient->get_client(), buffer.c_str(), buffer.length(), 0); // отправляем полученный буфер браузеру
	  }
	  else
		send(newclient->get_client(), heading::error404().c_str(), heading::error404().length(), 0);	
	 file.close();
}