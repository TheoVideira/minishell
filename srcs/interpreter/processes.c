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

static int		launch_processes(t_process *process, int save[2], t_list *cmd, t_minishell *mini)
{
	int i;
	int io[2];

	i = 0;
	while (cmd) 
	{
		open_pipe(i, io, save, cmd);// check error
		if ((process[i].pid = fork()) == 0)
		{
			build_cmd((t_cmd *)cmd->content, mini );// panic
			run_command((t_cmd *)cmd->content, mini); // check if label not found
		}
		else if (process[i].pid == -1)
		{
			// panic
		}
		close_pipe(io, cmd); 
		cmd = cmd->next;
		i++;
	}
	return (0);
}

static int		end_processes(t_process *process, int nb, t_minishell *mini)
{
	int i;

	i = -1;
	while (++i < nb)
	{
		waitpid(process[i].pid, &(process[i].status), 0);
		mini->lastcall = WIFEXITED(process[i].pid);
	}
	return (0);
}

int	run_processes(int save[2], int nb, t_list *cmds, t_minishell *mini)
{
	t_process *process;

	if (!(process = ft_calloc(1, sizeof(t_process) * nb)))
		return (-1);
	mini->envtmp = dictoenv(mini->env); // check error and if mini->env == 0
	launch_processes(process, save, cmds, mini); // check error
	end_processes(process, nb, mini); // check error
	dup2(save[0], 0);
	dup2(save[1], 1);
	free(process);
	free_char_array(mini->envtmp);
	return (0);
}

