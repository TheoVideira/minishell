#include <minishell.h>


static int	parse_parentheses(t_list **token, t_node **n)
{
	int r;

	destroyToken(token);
	r = parse_or(token, n);
	if (r != 0)
		return (r);
	if (*token && ft_strncmp(getToken(token), ")", 2) != 0)
		return (PARSING_ERROR);
	if (!*token)
	{
		while (1)
		{
			if (ask_for_more(token) != 0)
				return (FATAL_ERROR);
			if (ft_strncmp(getToken(token), ")", 2) == 0)
				break ;
			r = parse_or(token, n);
			if (r != 0)
				return (r);
			if (*token && ft_strncmp(getToken(token), ")", 2) == 0)
				break ;
		}
	} 
	printf("OK BOOMER\n");
	destroyToken(token);
	return (0);
}

static int	parse_commands(t_list **token, t_pipeline *p)
{
	int		r;
	t_list	*tmp;
	t_cmd	*c;

	while (*token)
	{
		r = parse_cmd(token, &c);
		if (r != 0)
			return (r);
		tmp = ft_lstnew(c);
		if (tmp == 0)
		{
			free_command(c);
			return (ALLOC_ERROR);
		}
		ft_lstadd_back(&p->cmds, tmp);
		if (*token && ft_strncmp(getToken(token), "|", 2) == 0)
		{
			destroyToken(token);
			if (!*token && ask_for_more(token) != 0)
			{
				free_command(c);
				return (FATAL_ERROR);
			}
		}		
		else if (*token && is_operator(getToken(token)))
			return (0);
	}
	return (r);
}

int		parse_pipeline(t_list **token, t_node **n)
{
	t_pipeline	*p;
	int			r;

	r = 0;
	if (!*token)
		return (PARSING_ERROR);
	if (ft_strncmp(getToken(token), "(", 2) == 0)
		return (parse_parentheses(token, n));
	if ((p = ft_calloc(1, sizeof(t_pipeline))) == 0)
		return (ALLOC_ERROR);
	r = parse_commands(token, p);
	if (r != 0)
		return (r);
	if ((*n = create_node(PIPELINE, p)) == 0)
		return (ALLOC_ERROR);
	return (0);
}