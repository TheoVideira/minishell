
#include <minishell.h>

int	format_arr(char **arr, t_minishell *mini)
{
	int i;
	char *tmp;

	i = 0;
	while (arr[i])
	{
		tmp = arr[i];
		arr[i] = format_arg(arr[i], mini);
		free(tmp);
		if (arr[i] == 0)
			return (2); // panic
		i++;
	}
	return (0);
}

int	build_cmd(t_cmd	*cmd, t_minishell *mini)
{
	if (cmd->args && format_arr(cmd->args, mini))
		return (1);
	if (cmd->redir && format_arr(cmd->redir, mini))
		return (1);
	cmd->label = cmd->args[0];
	return (0);
}

void		brutally_murder_childrens(t_minishell *mini)
{
	int i;

	i = 0;
	while (mini->childs[i].pid != 0)
	{
		kill(mini->childs[i].pid, SIGKILL);
		i++;
	}
	free(mini->childs);
	mini->childs = 0;
}
