/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:02:20 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 14:02:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	format_arr(char **arr)
{
	int i;
	char *tmp;

	i = 0;
	while (arr[i])
	{
		tmp = arr[i];
		arr[i] = format_arg(arr[i]);
		free(tmp);
		if (arr[i] == 0)
			return (2); // panic
		i++;
	}
	return (0);
}

int	build_cmd(t_cmd	*cmd)
{
	if (cmd->args && format_arr(cmd->args))
		return (1);
	if (cmd->redir && format_arr(cmd->redir))
		return (1);
	cmd->label = cmd->args[0];
	return (0);
}

void		brutally_murder_childrens(int sig)
{
	int i;

	if (mini.isparent == 0)
		return ;
	if (mini.childs == 0)
		return ;
	i = 0;
	while (mini.childs[i].pid != 0)
	{
		kill(mini.childs[i].pid, sig);
		i++;
	}
}
