#include <minishell.h>


static int	parse_parentheses(t_list **token, t_node **n)
{
	int r;

	destroyToken(token);
	r = parse_or(token, n);
	if (r == PARSING_ERROR)
		return (PARSING_ERROR);
	if (r == ALLOC_ERROR || !*token || ft_strncmp(getToken(token), ")", 2))
		return (PARSING_ERROR); // unexpcted end of line multiline ?
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
		if (ft_strncmp(getToken(token), "|", 2) == 0)
			destroyToken(token);
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
	}
	return (r);
}

int		parse_pipeline(t_list **token, t_node **n)
{
	t_pipeline	*p;
	int			r;

	r = 0;
	if (!*token)
		return (0);
	if (ft_strncmp(getToken(token), "(", 2) == 0)
		r = parse_parentheses(token, n);
	if (r != 0)
		return (r);
	if ((p = ft_calloc(1, sizeof(t_pipeline))) == 0)
		return (ALLOC_ERROR);
	r = parse_commands(token, p);
	if (r != 0)
		return (r);
	if ((*n = create_node(PIPELINE, p)) == 0)
		return (ALLOC_ERROR);
	return (0);
}