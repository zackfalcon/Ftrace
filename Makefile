##
## EPITECH PROJECT, 2018
## strace
## File description:
## makefile
##

CC	=	gcc

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -I./include/

NAME	=	ftrace

SRCS	=	src/main.c		\
		src/start_strace.c	\
		src/tools.c		\
		src/tools_sc.c		\
		src/display_type.c	\
		src/display_strace.c	\
		src/handle_signal.c

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS) -lelf

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
