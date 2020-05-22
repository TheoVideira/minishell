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
//Useless ?
typedef struct	s_minishell
{
	t_dict	*env;
	char	**envtmp;
	int		lastreturn;
	int		lastcall;
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

typedef struct	s_process
{
	pid_t pid;
	int status;
}				t_process;

typedef struct	s_entry
{
	t_list	*instructions;
	int		returned;
}				t_entry;

/*
**	Parse tree
*/
void	nextToken(t_list **token);
char	*getToken(t_list **token);
char	*getTokenHard(t_list **token);
void	destroyToken(t_list **token);
t_list	*popFirst(t_list **l);
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

/*
**	Lexer / tokenizer
*/
int		is_separator(char *str);
char	*handle_separators(char *str);
int		tokencount(char *str);
int		get_next_token(char *str, char **tofill);
int		tokenize(char *str, t_list **end);
int		replace_env(char **str, t_minishell *mini);
char	**list_to_char_array(t_list *l);

/*
**	Tree debugging
*/
void	print_node(t_node *n, int level);
void	print_tree(t_node *n);

/*
**	Pre exec build
*/
char	*format_arg(char *arg,  t_minishell *mini);
int		double_quotes(char *str, char **token,  t_minishell *mini);
int		single_quotes(char *str, char **token);
int		no_quotes(char *str, char **token,  t_minishell *mini);
/*
**	Execution
*/
int		handle_redirs(char **redirs);
int		build_cmd(t_cmd	*cmd, t_minishell *mini);
int		run_entry(t_entry *entry, t_minishell *mini);
int		run_tree(t_node *tree, t_minishell *mini);
int		run_pipeline(t_pipeline *pipe, t_minishell *mini);
int		run_processes(int save[2], int nb, t_list *cmds, t_minishell *mini);
int		run_command(t_cmd *cmd, t_minishell *mini);
char	**dictoenv(t_dict *dict);
int		is_builtin(t_cmd* cmd);
int		execute_builtin(t_cmd* cmd, t_minishell *mini);

/*
**	Built-ins
*/
void	ft_perror(char *shell, char *prg, char *arg);
void	ft_perror_msg(char *shell, char *prg, char *arg, char *msg);
int		builtin_echo(int ac, char* const* av);
int		builtin_cd(int ac, char* const* av, t_dict* env);
int		builtin_pwd(void);
int		builtin_export(int ac, char* const* av, t_dict *env);
int		builtin_unset(int ac, char* const* av, t_dict *env);
int		builtin_env(t_dict *env);
int		builtin_exit(int ac, char* const* av, t_minishell *mini);


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
#endif