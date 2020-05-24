#include <minishell.h>

int		tokenize(char *str, t_list **tokens)
{
	t_list	*new;
	char	*tok;
	int		tmp;

	*tokens = 0;
	while ((tmp = get_next_token(str, &tok)))
	{
		if (tmp == ALLOC_ERROR) 
			return (ALLOC_ERROR);
		if ((new = ft_lstnew(tok)) == 0)
		{
			free (tok);
			return (ALLOC_ERROR);
		}
		ft_lstadd_back(tokens, new); // check for new null
		str += tmp;
	}
	return (0);
}
