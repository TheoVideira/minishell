/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:01:44 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 14:01:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		open_pipe(int i, int io[2], int save[2], t_list *cmd)
{
	if (i > 0)
		dup2(io[0], 0);
	if (cmd->next)
	{
		pipe(io);
		dup2(io[1], 1);
	}
	else
		dup2(save[1], 1);
	return (0);
}

static int		close_pipe(int io[2], t_list *cmd)
{
		if (cmd->next)
			close(io[1]);
		return (0);
}

static int		launch_processes(int save[2], t_list *cmd)
{
	int i;
	int io[2];

	i = 0;
	while (cmd) 
	{
		open_pipe(i, io, save, cmd);// check error
		if ((mini.childs[i].pid = fork()) == 0)
		{
			// signal(SIGQUIT, 0);
			mini.isparent = 0;
			build_cmd((t_cmd *)cmd->content );// panic
			run_command((t_cmd *)cmd->content); // check if label not found
		}
		else if (mini.childs[i].pid == -1)
			return (FATAL_ERROR);
		close_pipe(io, cmd); 
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
		waitpid(mini.childs[i].pid, &(mini.childs[i].status), 0);
		mini.lastcall = WEXITSTATUS(mini.childs[i].status);
	}
	return (0);
}

int	run_processes(int save[2], int nb, t_list *cmds)
{
	int r;

	if (!(mini.childs = ft_calloc(1, sizeof(t_process) * (nb + 1))))
		return (ALLOC_ERROR);
	if (mini.env && (mini.envtmp = dictoenv(mini.env)) == 0)
		return (ALLOC_ERROR);
	if ((r = launch_processes(save, cmds)))
		brutally_murder_childrens(SIGKILL);
	else
		end_processes(nb);
	dup2(save[0], 0);
	dup2(save[1], 1);
	free(mini.childs);
	mini.childs = 0;
	free_char_array(mini.envtmp);
	return (r);
}

