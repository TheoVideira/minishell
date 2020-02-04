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

#include <libft.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <get_next_line.h>

//Useless ?
typedef struct	s_minishell
{
	t_list	*env;
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
	char	**input;
	int		fdout;
	int		fdin;
	int		returned;
}				t_cmd;

// /*
// **	;
// */
// t_list			*parse_string(char *str);
// /*
// **	|
// */
// t_pipeline		*parse_pipeline(char **str);
// /*
// **	Simple command
// */
// t_cmd			*parse_cmd(char **str);


int		tokencount(char *str);
char	**tokenize(char *str);
int		get_next_token(char *str, char **tofill);


/*
**	Execution
*/
// int				execute_instruction(t_instruction *p);
int				execute_pipeline(t_pipeline *p);
int				execute_command(t_cmd *p);

/*
**	Freeing
*/
// void			free_instruction(t_instruction *p);
void			free_pipeline(t_pipeline *p);
void			free_command(t_cmd *p);
void			free_tokenarray(char **tokens);
#endif