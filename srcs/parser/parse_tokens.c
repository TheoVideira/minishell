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

t_list	*popFirst(t_list **token)
{
	t_list *topop;

	topop = *token;
	*token = topop->next;
	topop->next = 0;
	return (topop);
}
