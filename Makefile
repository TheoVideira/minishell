CC = gcc
CFLAGS = -fsanitize=address -g3 -Wall -Wextra -Werror



GNL_SRCS =		gnl/get_next_line.c \
				gnl/get_next_line_utils.c
GNL_HEADERS =	gnl/get_next_line.h \


SRCS =		$(GNL_SRCS) \
			srcs/lexer/get_next_token.c \
			srcs/lexer/lexer_utils.c \
			srcs/lexer/tokenize.c \
			srcs/parser/parsing_utils.c \
			srcs/parser/parse_cmd.c \
			srcs/parser/parse_pipeline.c \
			srcs/parser/parse_entry.c \
			srcs/parser/parse_or.c \
			srcs/parser/parse_and.c \
			srcs/parser/parse_tokens.c \
			srcs/parser/ask_for_more.c \
			srcs/interpreter/env_formatting.c \
			srcs/interpreter/arg_formatting.c \
			srcs/interpreter/builtins.c \
			srcs/interpreter/processes.c \
			srcs/interpreter/processes_utils.c \
			srcs/interpreter/redirections.c \
			srcs/interpreter/run_command.c \
			srcs/interpreter/run_entry.c \
			srcs/interpreter/run_pipeline.c \
			srcs/interpreter/run_tree.c \
			srcs/builtins/builtins_cd.c \
			srcs/builtins/builtins_echo.c \
			srcs/builtins/builtins_env.c \
			srcs/builtins/builtins_exit.c \
			srcs/builtins/builtins_export.c \
			srcs/builtins/builtins_pwd.c \
			srcs/builtins/builtins_unset.c \
			srcs/misc/env.c \
			srcs/misc/errors.c \
			srcs/misc/tree.c \
			srcs/misc/freeing.c \
			srcs/misc/utils.c \
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
	