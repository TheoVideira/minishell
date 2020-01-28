CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c \

OBJS = $(SRCS:%.c=objs/%.o)

NAME = minishell

STATIC_LIB = libft/libft.a

INCLUDES = -I./libft

#Compilation
objs/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)


#
all: $(NAME)

libftplz:
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft fclean
	$(RM) -f $(OBJS)

fclean: clean
	$(RM) -f minishell

$(NAME) : libftplz $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LIB) $(INCLUDES) -o $(NAME)
	