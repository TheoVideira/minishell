/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 09:47:31 by user42            #+#    #+#             */
/*   Updated: 2020/06/24 12:25:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		open_pipe(int i, int io[2], int save[2], t_list *cmd)
{
	int r;

	r = 0;
	if (i > 0)
		r = dup2(io[0], 0);
	if (r == -1)
		return (fatal_error("dup2"));
	if (cmd->next)
	{
		r = pipe(io);
		if (r == -1)
			return (fatal_error("pipe"));
		r = dup2(io[1], 1);
		if (r == -1)
			return (fatal_error("dup2"));
	}
	else
		r = dup2(save[1], 1);
	if (r == -1)
		return (fatal_error("dup2"));
	return (0);
}

int		close_pipe(int io[2], t_list *cmd)
{
	int r;

	r = 0;
	if (cmd->next)
		r = close(io[1]);
	if (r == -1)
		return (fatal_error("close"));
	return (0);
}
