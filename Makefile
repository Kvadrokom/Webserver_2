#NAME := server
#NAME := client
# NAME := ft
NAME := webserver

#CC		=	clang++ -fsanitize=address
CC		=	clang++

CFLAGS	= 	-g -std=c++98 -Wall -Wextra -Werror

OBJDIR	=	objs
SRCDIR	=	src


#SRC :=  main_client.cpp
# SRC :=  main_server.cpp
# SRC :=  main_ft.cpp
SRC :=  main.cpp ASocket.cpp BindingSocket.cpp ListeningSocket.cpp Http_server.cpp AServer.cpp


SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))
OBJ		=	$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.cpp=.o))

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ):		|$(OBJDIR)

$(OBJDIR):
			@mkdir $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp includes/*.hpp
			$(CC) $(CFLAGS) -I ./includes -c $< -o $@

clean:
			@rm -rf $(OBJDIR)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

leak:
	export MallocStackLoggingNoCompact=1

valg:
	valgrind --leak-check=full

add:
	git add $(SRC) Makefile

free:
	rm -rf ~/Library/Caches/*	
	rm -rf ~/Library/42_cache	
	rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/	
	rm -rf ~/Library/Application\ Support/Slack/Cache/	
	rm -rf ~/Library/Application\ Support/Slack/Code\ Cache/
	rm -rf ~/Library/Application\ Support/Code/CachedData/*
	rm -rf ~/Library/Application\ Support/Code/Cache/*