CC = gcc
CFLAGS = -fsanitize=address -g3 -Wall -Wextra -Werror



GNL_SRCS =		gnl/get_next_line.c \
				gnl/get_next_line_utils.c
GNL_HEADERS =	gnl/get_next_line.h \


SRCS =		$(GNL_SRCS) \
			srcs/parser.c \
			srcs/freeing.c \
			srcs/main.c
HEADERS =	$(GNL_HEADERS) \
			headers/minishell.h \

OBJS = $(SRCS:%.c=objs/%.o)

NAME = minishell

STATIC_LIB = libft/libft.a

INCLUDES = -I./libft -I./headers -I./gnl

#Compilation
objs/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME)
bonus: $(NAME)

libftplz:
	$(MAKE) -C libft bonus

clean:
	$(MAKE) -C libft fclean
	$(RM) -f $(OBJS)

fclean: clean
	$(RM) -f minishell

re: fclean all

$(NAME) : libftplz $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LIB) $(INCLUDES) -o $(NAME)
	