/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:16:30 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 15:16:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		join_tokens(t_list **token, t_list **target)
{
	t_list	*toadd;
	char	*s1;
	char	*s2;
	char	*new;

	toadd = pop_first(token);
	s1 = toadd->content;
	if (!*token || is_operator(get_token(token)))
		return (ALLOC_ERROR);
	s2 = get_token_hard(token);
	if (!(new = ft_strjoin(s1, s2)))
		return (ALLOC_ERROR);
	toadd->content = new;
	free(s1);
	free(s2);
	ft_lstadd_back(target, toadd);
	return (0);
}

static int		parse_label(t_list **args, t_cmd **c, t_list **token)
{
	*args = 0;
	if ((*c = ft_calloc(1, sizeof(t_cmd))) == NULL)
		return (ALLOC_ERROR);
	ft_lstadd_back(args, pop_first(token));
	(*c)->label = (char*)(*args)->content;
	return (0);
}

static int		parse_args(t_list **token, t_list **args, t_list **redir)
{
	char	*t;

	*redir = 0;
	while (*token && !is_operator((t = get_token(token))))
	{
		if (ft_strncmp(t, ">", 2) == 0 ||
			ft_strncmp(t, ">>", 2) == 0 ||
			ft_strncmp(t, "<", 2) == 0)
		{
			if (join_tokens(token, redir) == ALLOC_ERROR)
				return (ALLOC_ERROR);
		}
		else
			ft_lstadd_back(args, pop_first(token));
	}
	return (0);
}

int				parse_cmd(t_list **token, t_cmd **c)
{
	int		r;
	t_list	*args;
	t_list	*redir;

	if (!*token || is_operator(get_token(token)))
		return (PARSING_ERROR);
	if (parse_label(&args, c, token) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	r = parse_args(token, &args, &redir);
	if (r == ALLOC_ERROR)
		return (ALLOC_ERROR);
	(*c)->args = list_to_char_array(args);
	(*c)->redir = list_to_char_array(redir);
	if ((ft_lstsize(args) && (*c)->args == 0) ||
		(ft_lstsize(redir) && (*c)->redir == 0))
		return (ALLOC_ERROR);
	ft_lstclear(&args, 0);
	ft_lstclear(&redir, 0);
	return (0);
}
