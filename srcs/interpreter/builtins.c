/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:02:04 by user42            #+#    #+#             */
/*   Updated: 2020/06/03 16:35:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		execute_builtin(t_cmd *c)
{
	if (!ft_strcmp(c->label, "echo"))
		return (builtin_echo(string_arr_size(c->args), c->args));
	if (!ft_strcmp(c->label, "cd"))
		return (builtin_cd(string_arr_size(c->args), c->args, g_mini.env));
	if (!ft_strcmp(c->label, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(c->label, "export"))
		return (builtin_export(string_arr_size(c->args), c->args, g_mini.env));
	if (!ft_strcmp(c->label, "unset"))
		return (builtin_unset(string_arr_size(c->args), c->args, g_mini.env));
	if (!ft_strcmp(c->label, "env"))
		return (builtin_env(g_mini.env));
	if (!ft_strcmp(c->label, "exit"))
		return (builtin_exit(string_arr_size(c->args), (char *const *)c->args));
	return (-1);
}

int		is_builtin(t_cmd *c)
{
	if (c->label == NULL)
		return (0);
	if (!ft_strcmp(c->label, "echo"))
		return (1);
	if (!ft_strcmp(c->label, "cd"))
		return (1);
	if (!ft_strcmp(c->label, "pwd"))
		return (1);
	if (!ft_strcmp(c->label, "export"))
		return (1);
	if (!ft_strcmp(c->label, "unset"))
		return (1);
	if (!ft_strcmp(c->label, "env"))
		return (1);
	if (!ft_strcmp(c->label, "exit"))
		return (1);
	return (0);
}
