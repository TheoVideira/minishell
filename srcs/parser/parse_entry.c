/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:04:13 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 15:09:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		parse_entry(t_list **tokens, t_entry **entry)
{
	int		r;
	char	*tok;
	t_node	*tree;
	t_list	*l;

	if ((*entry = ft_calloc(1, sizeof(t_entry))) == 0)
		return (ALLOC_ERROR);
	while ((tok = get_token(tokens)))
	{
		if (ft_strncmp(tok, ";", 2) == 0)
		{
			destroy_token(tokens);
			continue ;
		}
		r = parse_or(tokens, &tree);
		if (r != 0)
			return (r);
		if (!(l = ft_lstnew(tree)))
			return (ALLOC_ERROR);
		next_token(tokens);
		ft_lstadd_back(&(*entry)->instructions, l);
	}
	*tokens = 0;
	return (r);
}
