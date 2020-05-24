#include <minishell.h>

static int	run_single_builtin(int save[2], t_list *l, t_minishell *mini)
{
	int fd;

	if ((fd = handle_redirs(((t_cmd*)l->content)->redir)) != -1)
	{
		build_cmd((t_cmd *)l->content, mini);// panic
		mini->lastcall = execute_builtin((t_cmd *)l->content, mini); // check if label not found
		close(fd);
	}
	else
		mini->lastcall = 1;
	dup2(save[0], 0);
	dup2(save[1], 1);
	return (mini->lastcall);
}

int run_pipeline(t_pipeline *pi, t_minishell *mini)
{
	t_list *l;
	int len;
	int save[2];
	int r;

	l = pi->cmds;
	len = ft_lstsize(pi->cmds);
	save[0] = dup(0);
	save[1] = dup(1);
	if (len == 1 && is_builtin((t_cmd *)l->content))
		return (run_single_builtin(save, l, mini));
	if ((r = run_processes(save, len, pi->cmds, mini)))
		return (r);
	return (mini->lastcall); // value of pipe
}
