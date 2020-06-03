/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:50:20 by mclaudel          #+#    #+#             */
/*   Updated: 2020/06/03 02:13:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell g_mini = {0};

static void	run_dat_shit(char *line)
{
	t_list		*tokens;
	t_entry		*entry;

	if (ft_strlen(line) == 0 || is_only_space(line))
		return ;
	if (lexer(line, &tokens))
		return ;
	if (parser(&tokens, &entry))
		return ;
	interpreter(entry);
	free_entry(entry);
}

static void	init(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	g_mini.env = envtodict(env);
	g_mini.isparent = 1;
}

static void	quit(char *line)
{
	ft_dictclear(g_mini.env, free);
	free(line);
	write(1,"exit\n", 5);
	exit(g_mini.lastcall);
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
		r = get_next_line(0, &line);
		if (r == 0 && *line)
		{
			free(line);
			continue ;
		}
		if (r == 0)
			quit(line);
		run_dat_shit(line);
		free(line);
	}
	ft_dictclear(g_mini.env, free);
	return (g_mini.lastcall);
}
