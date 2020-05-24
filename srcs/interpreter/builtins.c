#include <minishell.h>

int		execute_builtin(t_cmd* cmd)
{
	if (!ft_strcmp(cmd->label, "echo"))
		return (builtin_echo(string_arr_size(cmd->args), cmd->args));
	if (!ft_strcmp(cmd->label, "cd"))
		return (builtin_cd(string_arr_size(cmd->args), cmd->args, mini.env));
	if (!ft_strcmp(cmd->label, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->label, "export"))
		return builtin_export(string_arr_size(cmd->args), cmd->args, mini.env);
	if (!ft_strcmp(cmd->label, "unset"))
		return builtin_unset(string_arr_size(cmd->args), cmd->args, mini.env);
	if (!ft_strcmp(cmd->label, "env"))
		return builtin_env(mini.env);
	if (!ft_strcmp(cmd->label, "exit"))
		return builtin_exit(string_arr_size(cmd->args), cmd->args);
	return (-1);
}

int		is_builtin(t_cmd* cmd)
{
	if (!ft_strcmp(cmd->label, "echo"))
		return (1);
	if (!ft_strcmp(cmd->label, "cd"))
		return (1);
	if (!ft_strcmp(cmd->label, "pwd"))
		return (1);
	if (!ft_strcmp(cmd->label, "export"))
		return (1);
	if (!ft_strcmp(cmd->label, "unset"))
		return (1);
	if (!ft_strcmp(cmd->label, "env"))
		return (1);
	if (!ft_strcmp(cmd->label, "exit"))
		return (1);
	return (0);
}