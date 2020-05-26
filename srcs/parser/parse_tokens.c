/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:09:58 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 15:09:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	next_token(t_list **token)
{
	if (*token)
		*token = (*token)->next;
}

char	*get_token(t_list **token)
{
	if ((char*)(*token))
		return ((char*)(*token)->content);
	return (0);
}

char	*get_token_hard(t_list **token)
{
	char	*tok;
	t_list	*tofree;

	tok = get_token(token);
	tofree = *token;
	next_token(token);
	free(tofree);
	return (tok);
}

void	destroy_token(t_list **token)
{
	t_list *tofree;

	tofree = *token;
	next_token(token);
	ft_lstdelone(tofree, free);
}

t_list	*pop_first(t_list **token)
{
	t_list *topop;

	topop = *token;
	*token = topop->next;
	topop->next = 0;
	return (topop);
}
