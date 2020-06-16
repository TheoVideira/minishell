/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 05:08:55 by user42            #+#    #+#             */
/*   Updated: 2020/06/14 22:35:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	run_single_builtin(int save[2], t_list *l)
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
	dup2(save[0], 0);
	dup2(save[1], 1);
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
		r = build_cmd(c);
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
	int		save[2];
	int		r;

	l = pi->cmds;
	len = ft_lstsize(pi->cmds);
	save[0] = dup(0);
	save[1] = dup(1);
	if (len == 1 && (r = is_single_builtin((t_cmd *)l->content)))
	{
		if (r < 0)
			return (r);
		r = run_single_builtin(save, l);
	}
	else
		r = run_processes(save, len, pi->cmds);
	if (r)
		return (r);
	return (g_mini.lastcall);
}
