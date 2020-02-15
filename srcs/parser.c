/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 11:23:51 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/04 18:26:52 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	nextToken(t_list **token)
{
	*token = (*token)->next;
}

char	*getToken(t_list **token)
{
	return ((char*)(*token)->content);
}

int		is_operator(char *str)
{
	if (*str == '&' && *(str + 1) == '&')
		return (2);
	if (*str == '|' && *(str + 1) == '|')
		return (2);
	if (*str == '(')
		return (1);
	if (*str == ')')
		return (1);
	if (*str == '|')
		return (1);
	if (*str == ';')
		return (1);
	return (0);
}

int		parse_instruction(t_list *tokens, t_instruction	**i)
{
	int	r;

	*i = ft_calloc(1, sizeof(t_instruction));
	r = parse_or(&tokens, &(*i)->tree);
	return (r);
}

int		parse_or(t_list **token, t_node **r)
{
	t_node *node;
	t_node *noder;

	node = 0;
	noder = 0;
	if (!*token)
		return 0;
	if (parse_and(token, &node) == -1)
		return (-1);
	while (*token && ft_strncmp(getToken(token), "||", 3) == 0)
	{
		nextToken(token);
		if (parse_and(token, &noder))
		{
			free_node(node);
			return (-1);
		}
		//add another code for malloc errors
		node = create_node_trio(OR, node, noder);
	}
	*r = node;
	return (0);
}

int		parse_and(t_list **token, t_node **r)
{
	t_node *node;
	t_node *noder;

	node = 0;
	noder = 0;
	if (!*token)
		return 0;
	if (parse_pipeline(token, &node) == -1)
		return (-1);
	while (*token && ft_strncmp(getToken(token), "&&", 3) == 0)
	{
		nextToken(token);
		if (parse_pipeline(token, &noder) == -1)
		{
			free_node(node);
			return (-1);
		}
		node = create_node_trio(AND, node, noder);
	}
	*r = node;
	return (0);
}

int		parse_pipeline(t_list **token, t_node **r)
{
	t_pipeline	*p;
	t_cmd		*c;

	if (!*token)
		return (0);
	if (ft_strncmp(getToken(token), "(", 2) == 0)
	{
		nextToken(token);
		parse_or(token, r);
		if(!*token || ft_strncmp(getToken(token), ")", 2))
			return (-1);
		nextToken(token);
		return (0);
	}
	
	if (!(p = ft_calloc(1, sizeof(t_pipeline))))
		return (-2);
	while ((parse_cmd(token, &c)) == 1) // Error check ?
	{
		ft_lstadd_back(&p->cmds, ft_lstnew(c)); //CHECK for NULL
		if (!*token || ft_strncmp(getToken(token), "|", 2))
			break;
		nextToken(token);
	}
	*r = create_node(PIPELINE, p);
	return (0);
}

//error code + error check
int		get_next_arg(t_list **token, t_list **target)
{
	t_list *tmp;

	tmp = *token;
	nextToken(token);
	if (!*token || is_operator(getToken(token)))
		return (-2);
	ft_lstadd_back(target, pop_next(tmp));
	*token = tmp;
	return (0);
}

t_list	*pop_next(t_list *l)
{
	t_list *topop;

	topop = l->next;
	l->next = topop->next;
	topop->next = 0;
	return (topop);
}

int		parse_cmd(t_list **token, t_cmd **c)
{
	int		r;
	char	*t;
	t_list	*tmp;

	if (!*token || is_operator(getToken(token)))
		return (0);
	if((*c = ft_calloc(1, sizeof(t_cmd))) == NULL)
		return (-1);
	(*c)->label = getToken(token);
	tmp = *token;
	nextToken(token);
	while (*token && !is_operator((t = getToken(token))))
	{
		r = 0;
		if (ft_strncmp(t, ">",2) == 0)
			r = get_next_arg(token, &(*c)->redir);
		else if (ft_strncmp(t, ">>",2) == 0)
			r = get_next_arg(token, &(*c)->hardredir);
		else if (ft_strncmp(t, "<",2) == 0)
			r = get_next_arg(token, &(*c)->input);
		else
		{
			ft_lstadd_back(&(*c)->args, pop_next(tmp));
			*token = tmp;
		}
		if (r < 0)
			return (-2);
		tmp = *token;
		nextToken(token);
	}
	return (1);
}