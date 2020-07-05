/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:16:30 by user42            #+#    #+#             */
/*   Updated: 2020/07/06 00:41:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		is_redir(char *str)
{
	return (ft_strncmp(str, ">", 2) == 0 ||
			ft_strncmp(str, ">>", 2) == 0 ||
			ft_strncmp(str, "<", 2) == 0);
}

static int		join_tokens(t_list **token, t_list **target)
{
	t_list	*toadd;
	char	*s1;
	char	*s2;
	char	*new;

	toadd = pop_first(token);
	s1 = toadd->content;
	s2 = get_token(token);
	if (!*token || is_operator(s2) || is_redir(s2))
	{
		ft_lstdelone(toadd, free);
		return (PARSING_ERROR);
	}
	s2 = get_token_hard(token);
	if (!(new = ft_strjoin(s1, s2)))
	{
		free(s1);
		free(s2);
		return (ALLOC_ERROR);
	}
	toadd->content = new;
	free(s1);
	free(s2);
	ft_lstadd_back(target, toadd);
	return (0);
}

static int		parse_args(t_list **token, t_list **args, t_list **redir)
{
	char	*t;
	int		r;

	*redir = 0;
	t = "";
	while (*token && !is_operator((t = get_token(token))))
	{
		if (is_redir(t))
		{
			if ((r = join_tokens(token, redir)))
				return (r);
		}
		else
			ft_lstadd_back(args, pop_first(token));
	}
	if (ft_strncmp(t, "(", 2) == 0)
		return (PARSING_ERROR);
	return (0);
}

static int		parse_label(t_list **args, t_cmd **c, t_list **token)
{
	t_list *new;

	*args = 0;
	if ((*c = ft_calloc(1, sizeof(t_cmd))) == NULL)
		return (ALLOC_ERROR);
	if (is_redir(get_token(token)))
	{
		if ((*token)->next == 0)
		{
			free(*c);
			*c = 0;
			return (PARSING_ERROR);
		}
		if ((new = ft_lstnew(0)) == 0)
		{
			free(*c);
			return (ALLOC_ERROR);
		}
	}
	else
		new = pop_first(token);
	ft_lstadd_back(args, new);
	(*c)->label = (char*)(*args)->content;
	return (0);
}

int				parse_cmd(t_list **token, t_cmd **c)
{
	int		r;
	t_list	*args;
	t_list	*redir;

	*c = 0;
	if (!*token || is_operator(get_token(token)))
		return (PARSING_ERROR);
	if ((r = parse_label(&args, c, token)))
		return (r);
	r = parse_args(token, &args, &redir);
	(*c)->args = list_to_char_array(args);
	(*c)->redir = list_to_char_array(redir);
	if (r == 0 && ((ft_lstsize(args) && (*c)->args == 0) ||
		(ft_lstsize(redir) && (*c)->redir == 0)))
		return (ALLOC_ERROR);
	ft_lstclear(&args, 0);
	ft_lstclear(&redir, 0);
	return (r);
}
