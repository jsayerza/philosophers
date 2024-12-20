CC				=	gcc
FLAGS			=	-g -Wextra -Werror -Wall #--sanitize=address
RM				=	rm -f
INCLUDES		=	-I.

NAME_SERVER     =	server
SERVER_SRC      =	server.c
SERVER_OBJ      =	$(SERVER_SRC:.c=.o)

NAME_CLIENT		=	client
CLIENT_SRC      =	client.c
CLIENT_OBJ      =	$(CLIENT_SRC:.c=.o)

NAME_SERVER_BONUS	=	server_bonus
SERVER_SRC_BONUS	=	server_bonus.c
SERVER_OBJ_BONUS	=	$(SERVER_SRC_BONUS:.c=.o)

NAME_CLIENT_BONUS	=	client_bonus
CLIENT_SRC_BONUS	=	client_bonus.c
CLIENT_OBJ_BONUS	=	$(CLIENT_SRC_BONUS:.c=.o)

UTILS_SRC       =	utils.c
UTILS_OBJ       =	$(UTILS_SRC:.c=.o)

FTPF_SRC		=	ftpf/ft_printf.c ftpf/ft_printf_utils.c
FTPF_OBJ		=	$(FTPF_SRC:.c=.o)

HEADERS			=	minitalk.h
HEADERS_BONUS	=	minitalk_bonus.h
HEADERS_UTILS	=	ftpf/ft_printf.h

all: 	$(NAME_SERVER) $(NAME_CLIENT)

bonus:	$(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER):	$(SERVER_OBJ) $(UTILS_OBJ) $(HEADERS) $(HEADERS_UTILS) $(FTPF_OBJ)
	$(CC) $(FLAGS) $(SERVER_OBJ) $(UTILS_OBJ) $(FTPF_OBJ) -o $(NAME_SERVER)
	
$(NAME_CLIENT):	$(CLIENT_OBJ) $(UTILS_OBJ) $(HEADERS) $(HEADERS_UTILS) $(FTPF_OBJ)
	$(CC) $(FLAGS) $(CLIENT_OBJ) $(UTILS_OBJ) $(FTPF_OBJ) -o $(NAME_CLIENT)

$(NAME_SERVER_BONUS):	$(SERVER_OBJ_BONUS) $(UTILS_OBJ) $(HEADERS_BONUS) $(HEADERS_UTILS) $(FTPF_OBJ)
	$(CC) $(FLAGS) $(SERVER_OBJ_BONUS) $(UTILS_OBJ) $(FTPF_OBJ) -o $(NAME_SERVER_BONUS)
	
$(NAME_CLIENT_BONUS):	$(CLIENT_OBJ_BONUS) $(UTILS_OBJ) $(HEADERS_BONUS) $(HEADERS_UTILS) $(FTPF_OBJ)
	$(CC) $(FLAGS) $(CLIENT_OBJ_BONUS) $(UTILS_OBJ) $(FTPF_OBJ) -o $(NAME_CLIENT_BONUS)

%.o: %.c Makefile $(HEADERS) $(HEADERS_BONUS) $(HEADERS_UTILS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C ftpf
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ) $(UTILS_OBJ) $(SERVER_OBJ_BONUS) $(CLIENT_OBJ_BONUS)

fclean:	clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

re:		fclean all

.PHONY:	all clean fclean re bonus


#valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./server
#valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./client