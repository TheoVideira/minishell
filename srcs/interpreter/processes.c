/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:01:44 by user42            #+#    #+#             */
/*   Updated: 2020/06/29 22:55:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		fork_process(int i, int io[2], int savedin, t_list *cmd)
{
	if ((g_mini.childs[i].pid = fork()) == 0)
	{
		if (i > 0)
			dup2(savedin, 0);
		if (cmd->next)
			dup2(io[1], 1);
		if (!(i == 0 && !cmd->next))
		{
			close(io[0]);
			close(io[1]);
		}
		g_mini.isparent = 0;
		build_cmd((t_cmd *)cmd->content);
		if (run_command((t_cmd *)cmd->content))
			exit(1);
	}
	else if (g_mini.childs[i].pid == -1)
		return (fatal_error("fork"));
	return (0);
}

static int		launch_processes(t_list *cmd)
{
	int i;
	int r;
	int io[2];
	int savedin;

	i = 0;
	io[0] = -1;
	io[1] = -1;
	savedin = -1;
	while (cmd)
	{
		if (cmd->next && pipe(io))
			return (fatal_error("pipe"));
		r = fork_process(i, io, savedin, cmd);
		if (r)
			return (r);
		if (savedin != -1 && close(savedin))
			return (fatal_error("close"));
		if (cmd->next && close(io[1]))
			return (fatal_error("close"));
		savedin = io[0];
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
		if (WIFEXITED(g_mini.childs[i].status))
			g_mini.lastcall = WEXITSTATUS(g_mini.childs[i].status);
	}
	return (0);
}

int				run_processes(int nb, t_list *cmds)
{
	int r;

	if (!(g_mini.childs = ft_calloc(1, sizeof(t_process) * (nb + 1))))
		return (ALLOC_ERROR);
	if (g_mini.env && dictoenv(g_mini.env) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	if ((r = launch_processes(cmds)))
		brutally_murder_childrens(SIGKILL);
	else
		end_processes(nb);
	free(g_mini.childs);
	g_mini.childs = 0;
	free_char_array(g_mini.envtmp);
	return (r);
}
