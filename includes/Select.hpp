#ifndef SELECT_HPP
#define SELECT_HPP

#include "Singleton.hpp"
#include "Http_server.hpp"

class Select : public Singleton<Select>
{
public:
	bool	can_read(int socket) const;
	bool	can_write(int socket) const;
	bool	update();
	void 	set_fd(int socket);
	void	clear_fd(int socket);
	void	set_max_fd(int max_fd);

			Select();

public:
	fd_set	m_clients;
	fd_set	m_read;
	fd_set	m_write;
	int		m_max_fd;

};

#endif