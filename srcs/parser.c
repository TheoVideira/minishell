/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 11:23:51 by mclaudel          #+#    #+#             */
/*   Updated: 2020/03/12 13:55:15 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	nextToken(t_list **token)
{
	if (*token)
		*token = (*token)->next;
}

char	*getToken(t_list **token)
{
	if ((char*)(*token))
		return ((char*)(*token)->content);
	return (0);
}

char	*getTokenHard(t_list **token)
{
	char *tok;
	t_list *tofree;

	tok = getToken(token);
	tofree = *token;
	nextToken(token);
	free(tofree);
	return (tok);
}

void	destroyToken(t_list **token)
{
	t_list *tofree;
	
	tofree = *token;
	nextToken(token);
	ft_lstdelone(tofree, free);
}

int		is_operator(char *str)
{
	if (*str == '&' && *(str + 1) == '&')
		return (2);
	if (*str == '|' && *(str + 1) == '|')
		return (2);
	if (*str == '(' && *(str + 1) == '\0')
		return (1);
	if (*str == ')' && *(str + 1) == '\0')
		return (1);
	if (*str == '|' && *(str + 1) == '\0')
		return (1);
	if (*str == ';' && *(str + 1) == '\0')
		return (1);
	return (0);
}

int		parse_entry(t_list **tokens, t_entry **entry)
{
	int		r;
	char	*tok;
	t_node	*tree;
	t_list	*l;

	*entry = ft_calloc(1, sizeof(t_entry));
	while ((tok = getToken(tokens)))
	{
		if (ft_strncmp(tok, ";", 2) == 0)
		{
			destroyToken(tokens);
			continue ;
		}
		r = parse_or(tokens, &tree);
		if (r != 0 || !(l = ft_lstnew(tree)))
		{
			//panic
			continue ;
		}
		nextToken(tokens);
		ft_lstadd_back(&(*entry)->instructions, l);
	}
	*tokens = 0;
	return (r);
}

int		parse_or(t_list **token, t_node **r)
{
	t_node *node;
	t_node *noder;


	node = 0;
	noder = 0;
	if (!*token)
		return (0);
	if (parse_and(token, &node) == -1)
		return (-1);
	while (*token && ft_strncmp(getToken(token), "||", 3) == 0)
	{
		destroyToken(token);
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
		return (0);
	if (parse_pipeline(token, &node) == -1)
		return (-1);
	while (*token && ft_strncmp(getToken(token), "&&", 3) == 0)
	{
		destroyToken(token);
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
		destroyToken(token);
		parse_or(token, r);
		if (!*token || ft_strncmp(getToken(token), ")", 2))
			return (-1);
		destroyToken(token);
		return (0);
	}
	if (!(p = ft_calloc(1, sizeof(t_pipeline))))
		return (-2);
	while ((parse_cmd(token, &c)) == 1) // Error check ?
	{
		ft_lstadd_back(&p->cmds, ft_lstnew(c)); //CHECK for NULL
		if (!*token || ft_strncmp(getToken(token), "|", 2))
			break ;
		destroyToken(token);
	}
	*r = create_node(PIPELINE, p);
	return (0);
}

//error code + error check
int		joinTokens(t_list **token, t_list **target)
{
	t_list *toadd;
	char *s1;
	char *s2;
	char *new;

	toadd = popFirst(token);
	s1 = toadd->content;
	if (!*token || is_operator(getToken(token)))
		return (-2);
	s2 = getTokenHard(token);
	if (!(new = ft_strjoin(s1, s2)))
		return (-2);
	toadd->content = new;
	free(s1);
	free(s2);
	ft_lstadd_back(target, toadd);
	return (0);
}

t_list	*popFirst(t_list **token)
{
	t_list *topop;

	topop = *token;
	*token = topop->next;
	topop->next = 0;
	return (topop);
}

int		parse_cmd(t_list **token, t_cmd **c)
{
	int		r;
	char	*t;

	if (!*token || is_operator(getToken(token)))
		return (0);
	if ((*c = ft_calloc(1, sizeof(t_cmd))) == NULL)
		return (-1);

	(*c)->label = getTokenHard(token);
	while (*token && !is_operator((t = getToken(token))))
	{
		r = 0;
		if (ft_strncmp(t, ">", 2) == 0 || ft_strncmp(t, ">>", 2) == 0)
			r = joinTokens(token, &(*c)->redir);
		else if (ft_strncmp(t, "<", 2) == 0)
			r = joinTokens(token, &(*c)->input);
		else
			ft_lstadd_back(&(*c)->args, popFirst(token)); // it calls nextToken() in any case
		if (r < 0)
			return (r);
	}
	return (1);
}
