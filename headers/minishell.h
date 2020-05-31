/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:41:15 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/04 17:44:19 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <get_next_line.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
# include <fcntl.h>

# define FATAL_ERROR -1
# define ALLOC_ERROR -2
# define PARSING_ERROR -3

typedef struct	s_process
{
	pid_t pid;
	int status;
}				t_process;

typedef struct	s_minishell
{
	t_dict		*env;
	t_process	*childs;
	int			isparent;
	char		**envtmp;
	int			lastreturn;
	int			lastcall;
}				t_minishell;

/*
**	A pipeline is a set of commands that returns 1 or 0
*/
typedef struct	s_pipeline
{
	t_list	*cmds;
	int		returned;
}				t_pipeline;


/*
**	Types of nodes in parse tree
*/
typedef enum	e_nodetype
{
	AND,
	OR,
	PIPELINE
}				t_nodetype;

/*
**	Basic structure for parse tree
*/
typedef struct s_node
{
	t_nodetype		type;
	t_pipeline 		*pipeline;
	struct s_node 	*left;
	struct s_node 	*right;
}				t_node;


/*
**	Simple command
*/
typedef struct	s_cmd
{
	char 	*label;
	char	**args;
	char	**redir;
	int		returned;
}				t_cmd;

typedef struct	s_entry
{
	t_list	*instructions;
	int		returned;
}				t_entry;

/*
**	Parse tree
*/
void	next_token(t_list **token);
char	*get_token(t_list **token);
char	*get_token_hard(t_list **token);
void	destroy_token(t_list **token);
t_list	*pop_first(t_list **l);
int		get_next_arg(t_list **token, t_list **target);
int		is_operator(char *str);
t_node	*create_node(t_nodetype t, t_pipeline *p);
t_node	*create_node_trio(t_nodetype t, t_node *left, t_node *right);
int		parse_entry(t_list **tokens, t_entry **i);
int		parse_or(t_list **tokens, t_node **r);
int		parse_and(t_list **tokens, t_node **r);
int		parse_pipeline(t_list **tokens, t_node **r);
int		parse_cmd(t_list **token, t_cmd **c);
int		ask_for_more(t_list **token);
int		replace_env(char **str);

/*
**	Lexer / tokenizer
*/
int		is_separator(char *str);
int		tokencount(char *str);
int		get_next_token(char *str, char **tofill);
int		tokenize(char *str, t_list **end);
char	**list_to_char_array(t_list *l);

/*
**	Tree debugging
*/
void	print_node(t_node *n, int level);
void	print_tree(t_node *n);

/*
**	Pre exec build
*/
int		format_arg(char *arg, char **into);
/*
**	Execution
*/
int		handle_redirs(char **redirs);
int		is_builtin(t_cmd* cmd);
int		execute_builtin(t_cmd* cmd);
int		build_cmd(t_cmd	*cmd);
int		run_entry(t_entry *entry);
int		run_tree(t_node *tree);
int		run_pipeline(t_pipeline *pipe);
int		run_processes(int save[2], int nb, t_list *cmds);
int		run_command(t_cmd *cmd);
void	brutally_murder_childrens(int sig);

/*
**	Signals
*/
void handle_sigint(int sig);
void handle_sigquit(int sig);

/*
**	Built-ins
*/
void	ft_perror(char *shell, char *prg, char *arg);
void	ft_perror_msg(char *shell, char *prg, char *arg, char *msg);
int		builtin_echo(int ac, char *const *av);
int		builtin_cd(int ac, char *const *av, t_dict* env);
int		builtin_pwd(void);
int		builtin_export(int ac, char *const *av, t_dict *env);
int		builtin_unset(int ac, char *const *av, t_dict *env);
int		builtin_env(t_dict *env);
int		builtin_exit(int ac, char* const* av);


/*
**	Freeing
*/
void			free_entry(t_entry *e);
void			free_pipeline(t_pipeline *p);
void			free_command(t_cmd *c);
void			free_char_array(char **arr);
void			free_node(t_node *tofree);

/*
**	Utils
*/
int		string_arr_size(char **args);

/*
**	Env
*/
t_dict	*envtodict(char **env);
char	**dictoenv(t_dict *dict);

/*
**	Error management
*/
void alloc_error();
void fatal_error();

extern t_minishell mini;
#endif