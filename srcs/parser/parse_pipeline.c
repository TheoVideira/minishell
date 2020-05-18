#include <minishell.h>


static int	parse_parentheses(t_list **token, t_node **n)
{
	destroyToken(token);
	parse_or(token, n);
	if (!*token || ft_strncmp(getToken(token), ")", 2))
		return (PARSING_ERROR); // unexpcted end of line multiline ?
	destroyToken(token);
	return (0);
}

int		parse_pipeline(t_list **token, t_node **n)
{
	t_pipeline	*p;
	t_cmd		*c;
	int			r;

	if (!*token)
		return (0);
	if (ft_strncmp(getToken(token), "(", 2) == 0 && parse_parentheses(token, n) == PARSING_ERROR)
		return (PARSING_ERROR);
	if (!(p = ft_calloc(1, sizeof(t_pipeline))))
		return (-2);
	while (( r = parse_cmd(token, &c)) == 1) // Error check ?
	{
		ft_lstadd_back(&p->cmds, ft_lstnew(c)); //CHECK for NULL
		if (!*token || ft_strncmp(getToken(token), "|", 2))
			break ;
		destroyToken(token);
	}
	*n = create_node(PIPELINE, p);
	return (0);
}