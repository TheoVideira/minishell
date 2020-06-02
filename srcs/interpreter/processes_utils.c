/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:02:20 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 23:10:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		format_arr(char **arr)
{
	int		i;
	int		r;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		tmp = arr[i];
		r = format_arg(arr[i], &(arr[i]));
		if (r)
			return (r);
		else
			free(tmp);
		i++;
	}
	return (0);
}

int		build_cmd(t_cmd *cmd)
{
	int r;

	if (cmd->args && (r = format_arr(cmd->args)))
		return (r);
	if (cmd->redir && (r = format_arr(cmd->redir)))
		return (r);
	cmd->label = cmd->args[0];
	return (0);
}

void	brutally_murder_childrens(int sig)
{
	int i;

	if (g_mini.isparent == 0)
		return ;
	if (g_mini.childs == 0)
		return ;
	i = 0;
	while (g_mini.childs[i].pid != 0)
	{
		kill(g_mini.childs[i].pid, sig);
		i++;
	}
}
