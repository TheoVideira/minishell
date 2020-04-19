#include <minishell.h>

int		echo(int ac, char* const* av)
{
	int i;
	int flagn;

	flagn = ac > 0 && ft_strcmp(av[0], "-n") == 0;
	i = flagn;
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