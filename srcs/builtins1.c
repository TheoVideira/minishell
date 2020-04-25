#include <minishell.h>

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
	char	*dir;

	if (ac > 2)
		return (1);
	if (!ac)
		dir = ft_dictget(env, "HOME");
	else
		dir = av[1];
	if (chdir(dir))
		ft_print_error("minishell", "cd", av[0]);
	return (0);
}

int		builtin_pwd(void)
{
	char *path;

	if (!(path = getcwd(NULL, 0)))
		ft_print_error("minishell", "pwd", NULL);
	write(1, path, ft_strlen(path));
	write(1, "\nabcd\n", 6);
	free(path);
	return (0);
}
