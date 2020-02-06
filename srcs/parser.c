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
	while (*token && ft_strncmp((char*)(*token)->content, "||", 3) == 0)
	{
		*token = (*token)->next;
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
	while (*token && ft_strncmp((char*)(*token)->content, "&&", 3) == 0)
	{
		*token = (*token)->next;
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
	if (ft_strncmp((char*)(*token)->content, "(", 2) == 0)
	{
		*token = (*token)->next;
		parse_or(token, r);
		if(!*token || ft_strncmp((char*)(*token)->content, ")", 2))
			return (-1);
		*token = (*token)->next;
		return (0);
	}
	
	if (!(p = ft_calloc(1, sizeof(t_pipeline))))
		return (-2);
	while ((parse_cmd(token, &c))) // Error check ?
	{
		ft_lstadd_back(&p->cmds, ft_lstnew(c)); //CHECK for NULL
		if (!*token || ft_strncmp((char*)(*token)->content, "|", 2))
			break;
	}
	*r = create_node(PIPELINE, p);
	return (0);
}

int		parse_cmd(t_list **token, t_cmd **c)
{
	char *t;

	if (!*token || is_operator((char*)(*token)->content))
		return (0);
	t = (char*)(*token)->content;
	if((*c = ft_calloc(1, sizeof(t_cmd))) == NULL)
		return (-1);
	(*c)->label = t;
	*token = (*token)->next;
	while (*token && !is_operator((char*)(*token)->content))
	{
		if (ft_strncmp(t, ">",2))
		
		if (ft_strncmp(t, "<",2))

		//args
		*token = (*token)->next;
		if (*token)
			t = (char*)(*token)->content;
	}
	return (1);
}