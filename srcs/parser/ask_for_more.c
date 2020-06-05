/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_for_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:04:56 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 03:42:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ask_for_more(t_list **token)
{
	int		r;
	char	*line;
	int		len;

	len = 0;
	while (len == 0)
	{
		write(1, ">", 1);
		r = get_next_line(0, &line);
		if (r == -1)
			return (fatal_error("get_next_line"));
		len = ft_strlen(line);
	}
	tokenize(line, token);
	free(line);
	return (0);
}
