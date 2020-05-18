#include "minishell.h"

static int ft_isnum(char *n)
{
	int i;

	i = 0;
	if (!n)
		return (0);
	if (n[i] == '-')
		i++;
	while(n[i])
		if (!ft_isdigit(n[i++]))
			return (0);
	return (1);
}

int		builtin_echo(int ac, char* const* av)
{
	int i;
	int flagn;

	flagn = ac > 1 && ft_strcmp(av[1], "-n") == 0;
	i = flagn + 1;
	while (i < ac)
	{
		write(1, av[i], ft_strlen(av[i]));
		if (i != ac - 1)
			write(1, " ", 1);
		i++;
	}
	if (!flagn)
		write(1, "\n", 1);
	return (0);
}

int		builtin_cd(int ac, char* const* av, t_dict* env)
{
	char *dir;
	char *oldpwd;
	char *key;

	oldpwd = NULL;
	if (ac > 2)
		return (1);
	if (!(key = ft_strdup("OLDPWD")) || !(oldpwd = getcwd(NULL, 0)))
	{
		ft_perror("minishell", "cd", NULL);
		free(key);
		free(oldpwd);
		return (1);
	}
	dir = (ac == 1) ? ft_dictget(env, "HOME") : av[1];
	if (chdir(dir))
	{
		ft_perror("minishell", "cd", dir);
		free(key);
		free(oldpwd);
		return (1);
	}
	ft_dictrem(&env, "OLDPWD", free);
	ft_dictadd(&env, ft_dictnew(key, oldpwd));
	return (0);
}

int		builtin_pwd(void)
{
	char *path;

	if (!(path = getcwd(NULL, 0)))
		ft_perror("minishell", "pwd", NULL);
	write(1, path, ft_strlen(path));
	write(1, "\nabcd\n", 6);
	free(path);
	return (0);
}

int	builtin_exit(int ac, char* const* av, t_minishell *mini)
{
	int exit_code;

	exit_code = mini->lastreturn;
	write(1, "exit\n", 5);
	if (ac == 1)
		exit(mini->lastreturn); //TODO (exit with previous code)
	if (ft_isnum(av[1]))	
		if (ac > 2)
			ft_perror_msg("minishell", "exit", NULL, "too many arguments\n");
		else
		{
			exit_code = ft_atoi(av[1]) % 255;
			exit_code = (exit_code < 0) ? 255 + exit_code + 1 : exit_code;
			exit(exit_code);
		}
	else
	{
		ft_perror_msg("minishell", "exit", av[1], "numeric argument required\n");
		exit(2);
	}
	return (1);
}

int builtin_env(t_dict *env)
{
	while (env)
	{
		write(1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write(1, env->value, ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}

int builtin_export(int ac, char* const* av, t_dict *env)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

	i = 0;
	while (++i < ac)
	{
		if ((eq = ft_strchr(av[i], '=')))
		{
			*eq = 0;
			ft_dictrem(&env, av[i], free);
			key = ft_strdup(av[i]);
			value = ft_strdup(eq + 1);
			ft_dictadd(&env, ft_dictnew(key, value));
		}
	}
	return(0);
}

int builtin_unset(int ac, char* const* av, t_dict *env)
{
	int i;

	i = 0;
	while (++i < ac)
		ft_dictrem(&env, av[i], free);
	return(0);
}