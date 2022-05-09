#include "Select.hpp"

bool	Select::can_read(int socket) const
{
	// if (select(m_max_fd + 1, &(fd_set)this->m_read, NULL, NULL, NULL) <= 0)
	// {
	// 		perror("select");
	// 		exit(3);
	// }
	if (FD_ISSET(socket, &m_read))
		return true;
	return false;
}

bool	Select::can_write(int socket) const
{
	// if (select(m_max_fd + 1, &(fd_set)this->m_write, NULL, NULL, NULL) <= 0)
	// {
	// 		perror("select");
	// 		exit(3);
	// }
	if (FD_ISSET(socket, &m_write))
		return true;
	return false;
}

bool	Select::update()
{
	return true;
}

void	Select::set_fd(int socket)
{
	FD_SET(socket, &m_clients);
}

void	Select::clear_fd(int socket)
{
	FD_CLR(socket, &m_read);
	FD_CLR(socket, &m_clients);
	FD_CLR(socket, &m_write);
}

void	Select::set_max_fd(int max_fd)
{
	this->m_max_fd = max_fd;
}

Select::Select()
{
	instance();
}