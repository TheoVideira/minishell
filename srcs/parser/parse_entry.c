/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:04:13 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 04:53:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_emptylines(t_list **tokens)
{
	destroy_token(tokens);
	if (ft_strncmp(get_token(tokens), ";", 1) == 0)
		return (PARSING_ERROR);
	return (0);
}

int		parse_entry(t_list **tokens, t_entry **entry)
{
	int		r;
	char	*tok;
	t_node	*tree;
	t_list	*l;

	if ((*entry = ft_calloc(1, sizeof(t_entry))) == 0)
		return (ALLOC_ERROR);
	if (ft_strncmp(get_token(tokens), ";", 1) == 0)
		return (PARSING_ERROR);
	while ((tok = get_token(tokens)))
	{
		if (ft_strncmp(tok, ";;", 3) == 0)
			return (PARSING_ERROR);
		if (ft_strncmp(tok, ";", 2) == 0 && (r = check_emptylines(tokens)))
			return (r);
		if ((r = parse_or(tokens, &tree)) != 0)
			return (r);
		if (!(l = ft_lstnew(tree)))
			return (ALLOC_ERROR);
		ft_lstadd_back(&(*entry)->instructions, l);
	}
	*tokens = 0;
	return (r);
}
