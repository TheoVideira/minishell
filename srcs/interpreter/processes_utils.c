/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:02:20 by user42            #+#    #+#             */
/*   Updated: 2020/05/31 16:58:26 by user42           ###   ########.fr       */
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
		free(tmp);
		if (r)
			return (r);
		i++;
	}
	return (0);
}

int		build_cmd(t_cmd *cmd)
{
	if (cmd->args && format_arr(cmd->args))
		return (1);
	if (cmd->redir && format_arr(cmd->redir))
		return (1);
	cmd->label = cmd->args[0];
	return (0);
}

void	brutally_murder_childrens(int sig)
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
