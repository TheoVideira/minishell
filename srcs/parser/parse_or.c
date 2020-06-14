/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_or.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:04:07 by user42            #+#    #+#             */
/*   Updated: 2020/06/14 19:55:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse_term(t_list **token, t_node **noder, t_node **node)
{
	int r;

	if (!*token && ask_for_more(token) != 0)
		return (FATAL_ERROR);
	if ((r = parse_and(token, noder)) != 0)
	{
		free_node(*node);
		return (r);
	}
	if ((*node = create_node_trio(OR, *node, *noder)) == 0)
	{
		free_node(*node);
		return (ALLOC_ERROR);
	}
	return (0);
}

int			parse_or(t_list **token, t_node **n)
{
	t_node	*node;
	t_node	*noder;
	int		r;

	node = 0;
	noder = 0;
	if (!*token)
		return (0);
	if ((r = parse_and(token, &node)) != 0)
	{
		free_node(node);
		return (r);
	}
	while (*token && ft_strncmp(get_token(token), "||", 3) == 0)
	{
		destroy_token(token);
		if ((r = parse_term(token, &noder, &node)))
			return (r);
	}
	*n = node;
	return (0);
}
