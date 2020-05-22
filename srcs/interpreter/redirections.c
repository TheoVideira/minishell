#include <minishell.h>

static int		redir_open_out_append(char **redirs, int i, int foi[2])
{
	int fd;

	if (foi[0] != -1)
		close(foi[0]);
	if ((fd = open(redirs[i] + 2, O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
	{
		ft_perror("minishell", redirs[i] + 2, 0);
		return (fd);
	}
	foi[0] = fd;
	dup2(fd, 1);
	return (fd);
}

static int		redir_open_out(char **redirs, int i, int foi[2])
{
	int fd;

	if (foi[0] != -1)
		close(foi[0]);
	if ((fd = open(redirs[i] + 1, O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
	{
		ft_perror("minishell", redirs[i] + 1, 0);
		return (fd);
	}
	foi[0] = fd;
	dup2(fd, 1);
	return (fd);
}

static int		redir_open_in(char **redirs, int i, int foi[2])
{
	int fd;

	if (foi[1] != -1)
		close(foi[1]);
	if ((fd = open(redirs[i] + 1, O_RDONLY)) == -1)
	{
		ft_perror("minishell", redirs[i] + 1, 0);
		return (fd);
	}
	foi[1] = fd;
	dup2(fd, 0);
	return (fd);
}

int handle_redirs(char **redirs)
{
	int i;
	int fd;
	int foi[2] = { -1, -1 };

	i = 0;
	if (!redirs)
		return (0);
	while (redirs[i])
	{
		if (ft_strncmp(">>", redirs[i], 2) == 0)
			fd = redir_open_out_append(redirs, i, foi);
		else if (ft_strncmp(">", redirs[i], 1) == 0)
			fd = redir_open_out(redirs, i, foi);
		else if (ft_strncmp("<", redirs[i], 1) == 0)
			fd = redir_open_in(redirs, i, foi);
		if (fd == -1)
			break ;
		i++;
	}
	return (fd);
}