/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:01:27 by user42            #+#    #+#             */
/*   Updated: 2020/07/01 19:31:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		redir_open_out_append(char **redirs, int i, int foi[2])
{
	int fd;

	if (foi[0] != -1)
		close(foi[0]);
	if ((fd = open(redirs[i] + 2, O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
	{
		return (fatal_error(redirs[i] + 2));
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
		return (fatal_error(redirs[i] + 1));
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
		return (fatal_error(redirs[i] + 1));
	}
	foi[1] = fd;
	dup2(fd, 0);
	return (fd);
}

int				handle_redirs(char **redirs)
{
	int i;
	int fd;
	int foi[2];

	i = 0;
	foi[0] = -1;
	foi[1] = -1;
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
