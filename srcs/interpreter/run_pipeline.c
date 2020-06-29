/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 05:08:55 by user42            #+#    #+#             */
/*   Updated: 2020/06/24 16:42:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	run_single_builtin(t_list *l)
{
	int	fd;
	int	r;

	if ((fd = handle_redirs(((t_cmd*)l->content)->redir)) != -1)
	{
		if ((r = build_cmd((t_cmd *)l->content)))
			return (r);
		g_mini.lastcall = execute_builtin((t_cmd *)l->content);
		close(fd);
	}
	else
		g_mini.lastcall = 1;
	return (g_mini.lastcall);
}

static int	is_single_builtin(t_cmd *c)
{
	int r;

	if ((r = format_arg(c->args[0], &(c->label))))
		return (r);
	if (is_builtin(c))
	{
		free(c->label);
		if (r)
			return (r);
		return (1);
	}
	free(c->label);
	return (0);
}

int			run_pipeline(t_pipeline *pi)
{
	t_list	*l;
	int		len;
	int		r;

	l = pi->cmds;
	len = ft_lstsize(pi->cmds);
	if (len == 1 && (r = is_single_builtin((t_cmd *)l->content)))
	{
		if (r < 0)
			return (r);
		r = run_single_builtin(l);
	}
	else
		r = run_processes(len, pi->cmds);
	if (r)
		return (r);
	return (g_mini.lastcall);
}
