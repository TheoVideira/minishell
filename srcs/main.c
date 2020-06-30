/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:50:20 by mclaudel          #+#    #+#             */
/*   Updated: 2020/06/30 11:55:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell g_mini = {0};

// PENSER A ENLEVER LE FSANITIZE DU MAKEFILE

static void	init(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	if (env && *env)
	{
		g_mini.env = envtodict(env);
		if (g_mini.env == 0)
		{
			alloc_error();
			exit(1);
		}
	}
	else
		g_mini.env = 0;
	g_mini.isparent = 1;
}

static void	quit(char *line)
{
	ft_dictclear(g_mini.env, free);
	free(line);
	write(1, "exit\n", 5);
	exit(g_mini.lastcall);
}

static void	quit_error(char *line, char *func)
{
	ft_dictclear(g_mini.env, free);
	if (line)
		free(line);
	fatal_error(func);
	exit(1);
}

static int	handle_eof(char **line)
{
	int		r;
	char	*prev;
	char	*curr;
	char	*new;

	prev = *line;
	new = *line;
	curr = 0;
	while ((r = get_next_line(0, &curr)) == 0 && curr)
	{
		new = ft_strjoin(prev, curr);
		free(prev);
		free(curr);
		prev = new;
		if(!new)
			return (-1);
	}
	if (r == -1)
		return (-1);
	if(!(*line = ft_strjoin(new, curr)))
		return (-1);
	free(new);
	free(curr);
	return (1);
}

int			main(int ac, char **av, char **env)
{
	int			r;
	char		*line;

	r = 1;
	line = 0;
	init(ac, av, env);
	while (1)
	{
		if (r != 0)
			write(1, "\e[1;35mOK-BOOMER\e[0m$>", 23);
		if ((r = get_next_line(0, &line)) == -1)
			quit_error(line, "get_next_line");
		if (r == 0 && *line)
		{
			if ((r = handle_eof(&line)) == -1)
				quit_error(line, "handle_eof");
		}
		else if (r == 0)
			quit(line);
		run_dat_shit(line);
		free(line);
	}
	ft_dictclear(g_mini.env, free);
	return (g_mini.lastcall);
}
