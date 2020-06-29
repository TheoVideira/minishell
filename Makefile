CC = gcc
CFLAGS = -Wall -Wextra -Werror

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
			srcs/interpreter/search_directory.c \
			srcs/interpreter/arg_formatting.c \
			srcs/interpreter/escaped_characters.c \
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
			srcs/builtins/builtins_export_add.c \
			srcs/builtins/builtins_export_print.c \
			srcs/builtins/builtins_pwd.c \
			srcs/builtins/builtins_unset.c \
			srcs/misc/signals.c \
			srcs/misc/env.c \
			srcs/misc/errors.c \
			srcs/misc/tree.c \
			srcs/misc/freeing.c \
			srcs/misc/utils.c \
			srcs/main_utils.c \
			srcs/main.c


HEADERS =	$(GNL_HEADERS) \
			headers/minishell.h \

OBJ_PARENT_DIR = objs

OBJS_DIR =	$(OBJ_PARENT_DIR) \
			$(OBJ_PARENT_DIR)/gnl \
			$(OBJ_PARENT_DIR)/srcs \
			$(OBJ_PARENT_DIR)/srcs/lexer \
			$(OBJ_PARENT_DIR)/srcs/parser \
			$(OBJ_PARENT_DIR)/srcs/interpreter \
			$(OBJ_PARENT_DIR)/srcs/builtins \
			$(OBJ_PARENT_DIR)/srcs/misc

OBJS = $(SRCS:%.c=$(OBJ_PARENT_DIR)/%.o)

NAME = minishell

STATIC_LIB = libft/libft.a

INCLUDES = -I./libft -I./headers -I./gnl

#Compilation
$(OBJ_PARENT_DIR)/%.o: %.c $(HEADERS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

bonus: $(NAME)

$(STATIC_LIB):
	$(MAKE) -C libft bonus

clean:
	$(MAKE) -C libft clean
	$(RM) -f $(OBJS)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) -f minishell

re: fclean all

$(NAME) : $(STATIC_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(STATIC_LIB) -o $(NAME)

$(OBJS_DIR) :
	mkdir -p  $(OBJS_DIR)

