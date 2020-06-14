/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:33:59 by user42            #+#    #+#             */
/*   Updated: 2020/06/12 17:02:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse_parentheses(t_list **token, t_node **n)
{
	int r;

	destroy_token(token);
	r = parse_or(token, n);
	if (r != 0)
		return (r);
	if (*token && ft_strncmp(get_token(token), ")", 2) != 0)
		return (PARSING_ERROR);
	if (!*token)
	{
		while (1)
		{
			if ((r = ask_for_more(token)))
				return (r);
			if (ft_strncmp(get_token(token), ")", 2) == 0)
				break ;
			r = parse_or(token, n);
			if (r != 0)
				return (r);
			if (*token && ft_strncmp(get_token(token), ")", 2) == 0)
				break ;
		}
	}
	destroy_token(token);
	return (0);
}

static int	return_and_free(t_cmd *c, int code)
{
	free_command(c);
	return (code);
}

static int	parse_commands(t_list **token, t_pipeline *p)
{
	int		r;
	t_list	*tmp;
	t_cmd	*c;

	while (*token)
	{
		if ((r = parse_cmd(token, &c)) != 0)
		{
			if (c)
				free_command(c);
			return (r);
		}
		if ((tmp = ft_lstnew(c)) == 0)
			return (return_and_free(c, ALLOC_ERROR));
		ft_lstadd_back(&p->cmds, tmp);
		if (*token && ft_strncmp(get_token(token), "|", 2) == 0)
		{
			destroy_token(token);
			if (!*token && (r = ask_for_more(token)))
				return (FATAL_ERROR);
		}
		else if (*token && is_operator(get_token(token)))
			return (0);
	}
	return (r);
}

int			parse_pipeline(t_list **token, t_node **n)
{
	t_pipeline	*p;
	int			r;

	r = 0;
	if (!*token)
		return (PARSING_ERROR);
	if (ft_strncmp(get_token(token), "(", 2) == 0)
		return (parse_parentheses(token, n));
	if ((p = ft_calloc(1, sizeof(t_pipeline))) == 0)
		return (ALLOC_ERROR);
	r = parse_commands(token, p);
	if (r != 0)
	{
		free_pipeline(p);
		return (r);
	}
	if ((*n = create_node(PIPELINE, p)) == 0)
		return (ALLOC_ERROR);
	return (0);
}
