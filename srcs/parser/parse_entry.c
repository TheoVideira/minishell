/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:04:13 by user42            #+#    #+#             */
/*   Updated: 2020/06/12 17:15:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_emptylines(char *tok, t_list **tokens)
{
	if (ft_strncmp(tok, ";;", 3) == 0)
		return (PARSING_ERROR);
	if (ft_strncmp(tok, ";", 2) == 0)
	{
		destroy_token(tokens);
		if ((tok = get_token(tokens)) && ft_strncmp(tok, ";", 1) == 0)
			return (PARSING_ERROR);
		return (1);
	}
	return (0);
}

int			parse_entry(t_list **tokens, t_entry **entry)
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
		if ((r = check_emptylines(tok, tokens)) == 1
				&& !(r = 0))
			continue ;
		else if (r < 0)
			return (r);
		tree = 0;
		if ((r = parse_or(tokens, &tree)) != 0)
		{
			free_node(tree);
			return (r);
		}
		if (!(l = ft_lstnew(tree)))
			return (ALLOC_ERROR);
		ft_lstadd_back(&(*entry)->instructions, l);
	}
	*tokens = 0;
	return (r);
}
