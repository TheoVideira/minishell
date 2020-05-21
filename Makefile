CC = gcc
CFLAGS = -fsanitize=address -g3 -Wall -Wextra -Werror



GNL_SRCS =		gnl/get_next_line.c \
				gnl/get_next_line_utils.c
GNL_HEADERS =	gnl/get_next_line.h \


SRCS =		$(GNL_SRCS) \
			srcs/freeing.c \
			srcs/tree.c	\
			srcs/tokenizer.c \
			srcs/tokenizer2.c \
			srcs/interpreter.c \
			srcs/interpreter_utils.c \
			srcs/builtins1.c \
			srcs/builtins_utils.c \
			srcs/utils.c \
			srcs/main.c \
			srcs/parser/parse_cmd.c \
			srcs/parser/parse_pipeline.c \
			srcs/parser/parse_entry.c \
			srcs/parser/parse_or.c \
			srcs/parser/parse_and.c \
			srcs/parser/parse_tokens.c \
			srcs/parser/ask_for_more.c

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
	