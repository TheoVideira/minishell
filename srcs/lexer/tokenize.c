/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:00:08 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 15:00:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		tokenize(char *str, t_list **tokens)
{
	t_list	*new;
	char	*tok;
	int		tmp;

	*tokens = 0;
	while ((tmp = get_next_token(str, &tok)))
	{
		if (tmp == ALLOC_ERROR)
			return (ALLOC_ERROR);
		if ((new = ft_lstnew(tok)) == 0)
		{
			free(tok);
			return (ALLOC_ERROR);
		}
		ft_lstadd_back(tokens, new);
		str += tmp;
	}
	return (0);
}
