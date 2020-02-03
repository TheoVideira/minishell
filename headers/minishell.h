/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:41:15 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/03 16:32:49 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <libft.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <get_next_line.h>

typedef struct	s_minishell
{
	t_list	*env;
}				t_minishell;


/*
**	&& || ( )
*/
typedef struct	s_instruction
{
	t_list	*pipelines;
	int		returned;
}				t_instruction;

/*
**	|
*/
typedef struct	s_pipeline
{
	t_list	*cmds;
	int		returned;
}				t_pipeline;

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
	int		returned;
}				t_cmd;

/*
**	;
*/
t_list			*parse_string(char *str);
/*
**	&& ||
*/
t_instruction	*parse_instruction(char **str);
/*
**	|
*/
t_pipeline		*parse_pipeline(char **str);
/*
**	Simple command
*/
t_cmd			*parse_cmd(char **str);


int		tokencount(char *str);
char	**tokenize(char *str);
char	*get_next_token(char *str);


/*
**	Execution
*/
int				execute_instruction(t_instruction *p);
int				execute_pipeline(t_pipeline *p);
int				execute_command(t_cmd *p);

/*
**	Freeing
*/
void			free_instruction(t_instruction *p);
void			free_pipeline(t_pipeline *p);
void			free_command(t_cmd *p);
void			free_tokenarray(char **tokens);
#endif