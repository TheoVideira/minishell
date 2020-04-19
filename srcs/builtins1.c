#include <minishell.h>

int		echo(int ac, char **av)
{
	int i;
	int flagn;

	flagn = ac > 1 && ft_strcmp(av[1], "-n") == 0;
	printf("%d \n", flagn);
	i = 1 + flagn;
	while (i < ac)
	{
		write(1, av[i], ft_strlen(av[i]));
		write(1, " ", 1);
		i++;
	}
	if (flagn)
		write(1, "\n", 1);
	return (0);
}