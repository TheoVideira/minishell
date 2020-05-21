#include <minishell.h>

int		parse_and(t_list **token, t_node **n)
{
	t_node *node;
	t_node *noder;
	int r;

	node = 0;
	noder = 0;
	if (!*token)
		return (0);
	if ((r = parse_pipeline(token, &node)) != 0)
		return (r);
	while (*token && ft_strncmp(getToken(token), "&&", 3) == 0)
	{
		destroyToken(token);
		if (!*token && ask_for_more(token) != 0)
			return (FATAL_ERROR);
		if ((r = parse_pipeline(token, &noder)) != 0)
		{
			free_node(node);
			return (r);
		}
		if ((node = create_node_trio(AND, node, noder)) == 0)
			return (ALLOC_ERROR);
	}
	printf("and\n");
	*n = node;
	return (0);
}
