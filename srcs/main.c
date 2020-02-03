/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:50:20 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/03 15:49:25 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	int				r;
	// t_instruction	*job;

	char	*line;
	while (1)
	{
		write(1, "$>", 3);
		r = get_next_line(0, &line);
		// if (r == -1)
		// 	if (errno)
		// 		perror(strerror(errno));
		// //Parse
		// job = parse_instruction(line);
		// //Execute
		// execute_instruction(job);
		// free_instruction(job);
		// if (r == 0)
		// {
		// 	free(line);
		// 	break ;
		// }
		
		char **tokens = tokenize(line);
		int i = 0;
		while (tokens[i])
		{
			printf("\"%s\"\n", tokens[i]);
			i++;
		}
		printf("Just parsed \"%s\"\n", line);
		free(line);
		free_tokenarray(tokens);
	}
	//Think about freeing if signal caught
	return (0);
}
