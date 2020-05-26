/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:12:13 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 15:12:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		parse_and(t_list **token, t_node **n)
{
	t_node	*node;
	t_node	*noder;
	int		r;

	node = 0;
	noder = 0;
	if (!*token)
		return (0);
	if ((r = parse_pipeline(token, &node)) != 0)
		return (r);
	while (*token && ft_strncmp(get_token(token), "&&", 3) == 0)
	{
		destroy_token(token);
		if (!*token && ask_for_more(token) != 0)
			return (FATAL_ERROR);
		if ((r = parse_pipeline(token, &noder)) != 0)
		{
			free_node(node);
			return (r);
		}
		if ((node = create_node_trio(AND, node, noder)) == 0)
			return (ALLOC_ERROR);
	}
	*n = node;
	return (0);
}
