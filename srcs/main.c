/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:50:20 by mclaudel          #+#    #+#             */
/*   Updated: 2020/06/02 21:36:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell mini = {0};

static void run_dat_shit(char *line)
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

int main(int ac, char **av, char **env)
{
	int			r;
	char		*line;
	
	(void) ac;
	(void) av;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	mini.env = envtodict(env);
	mini.isparent = 1;
	r = 1;
	line = 0;
	while (1)
	{
		if (r != 0)
			write(1, "\e[1;35mOK-BOOMER\e[0m$>", 23);
		r = get_next_line(0, &line);
		if (r == 0 && *line)
		{
			free (line);
			continue ;
		}
		if (r == 0)
		{
			ft_dictclear(mini.env, free);
			free(line);
			builtin_exit(1, 0);
		}
		run_dat_shit(line);
		free(line);
	}
	ft_dictclear(mini.env, free);
	return (0);
}
