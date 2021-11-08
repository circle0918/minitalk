SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: server client

bonus: server_bonus client_bonus

server: outils.o ft_server.o
	gcc -o server ft_server.o outils.o

client: outils.o ft_client.o
	gcc -o client ft_client.o outils.o 

server_bonus: outils.o ft_server_bonus.o
	gcc -o server_bonus ft_server_bonus.o outils.o

client_bonus: outils.o ft_client_bonus.o
	gcc -o client_bonus ft_client_bonus.o outils.o 

%.o: %.c
	gcc -c -Wall -Wextra -Werror $?

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f server client server_bonus client_bonus

re: fclean all

.PHONY: all clean fclean re
