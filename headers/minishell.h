/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:41:15 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/28 18:12:17 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <libft.h>

typedef struct	s_minishell
{
	t_list	*env;
}				t_minishell;


/*
**	&& ||
*/
typedef struct	s_instruction
{
	t_list	*pipelines;
	int		returned;
}				t_intruction;

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
	char	**args;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         args;
	char	**redir;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      args;
	char	**input;
	int		fdin;
	int		fdout;
	int		returned;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        args;
}				t_cmd;

/*
**	;
*/
t_list			*parse_string(char *str);
/*
**	&& ||
*/
t_cmd			*parse_instruction(char *str);
/*
**	|
*/
t_cmd			*parse_pipeline(char *str);
/*
**	Simple command
*/
t_cmd			*parse_cmd(char *str);

void			print_tree(char *str);
#endif