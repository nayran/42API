NAME = intra

LIBS=/usr/lib/

SRCS = main.c			\
	   curl.c		\
	   mysql.c		\
	   utils.c		\
	   ulfius.c		\
	   usertable.c		\
	   projectstable.c	\
	   cursustable.c	\
	   print.c


OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra 

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(FLAGS) $(OBJS) -o $(NAME) -ljson-c -lcurl -lmysqlclient -lulfius 

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
