#include <minishell.h>

int		parse_entry(t_list **tokens, t_node **root)
{
	int		r;
	char	*tok;
	t_node	*tree;
	t_list	*l;
	t_entry *entry;

	if ((entry = ft_calloc(1, sizeof(t_entry))) == 0)
		return (ALLOC_ERROR);
	if ((*root = create_node(ENTRY, entry)) == 0)
	{
		free(entry);
		return (ALLOC_ERROR);
	}
	while ((tok = getToken(tokens)))
	{
		if (ft_strncmp(tok, ";", 2) == 0)
		{
			destroyToken(tokens);
			continue ;
		}
		r = parse_or(tokens, &tree);
		if (r != 0)
			return (r);
		if (!(l = ft_lstnew(tree)))
			return (ALLOC_ERROR);
		nextToken(tokens);
		ft_lstadd_back(&entry->instructions, l);
	}
	return (r);
}
