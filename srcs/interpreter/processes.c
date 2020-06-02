/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:01:44 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 23:10:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		fork_process(int i, t_list *cmd)
{
	if ((g_mini.childs[i].pid = fork()) == 0)
	{
		g_mini.isparent = 0;
		build_cmd((t_cmd *)cmd->content);
		if (run_command((t_cmd *)cmd->content))
			exit(1);
	}
	else if (g_mini.childs[i].pid == -1)
		return (FATAL_ERROR);
	return (0);
}

static int		launch_processes(int save[2], t_list *cmd)
{
	int i;
	int r;
	int io[2];

	i = 0;
	while (cmd)
	{
		r = open_pipe(i, io, save, cmd);
		if (r)
			return (r);
		r = fork_process(i, cmd);
		if (r)
			return (r);
		r = close_pipe(io, cmd);
		if (r)
			return (r);
		cmd = cmd->next;
		i++;
	}
	return (0);
}

static int		end_processes(int nb)
{
	int i;

	i = -1;
	while (++i < nb)
	{
		waitpid(g_mini.childs[i].pid, &(g_mini.childs[i].status), 0);
		g_mini.lastcall = WEXITSTATUS(g_mini.childs[i].status);
	}
	return (0);
}

int				run_processes(int save[2], int nb, t_list *cmds)
{
	int r;

	if (!(g_mini.childs = ft_calloc(1, sizeof(t_process) * (nb + 1))))
		return (ALLOC_ERROR);
	if (g_mini.env && (g_mini.envtmp = dictoenv(g_mini.env)) == 0)
		return (ALLOC_ERROR);
	if ((r = launch_processes(save, cmds)))
		brutally_murder_childrens(SIGKILL);
	else
		end_processes(nb);
	dup2(save[0], 0);
	dup2(save[1], 1);
	free(g_mini.childs);
	g_mini.childs = 0;
	free_char_array(g_mini.envtmp);
	return (r);
}
