#include <minishell.h>

static int		joinTokens(t_list **token, t_list **target)
{
	t_list *toadd;
	char *s1;
	char *s2;
	char *new;

	toadd = popFirst(token);
	s1 = toadd->content;
	if (!*token || is_operator(getToken(token)))
		return (ALLOC_ERROR);
	s2 = getTokenHard(token);
	if (!(new = ft_strjoin(s1, s2)))
		return (ALLOC_ERROR);
	toadd->content = new;
	free(s1);
	free(s2);
	ft_lstadd_back(target, toadd);
	return (0);
}

static int		parse_label(t_list **args, t_cmd **c, t_list **token)
{
	*args = 0;
	if ((*c = ft_calloc(1, sizeof(t_cmd))) == NULL)
		return (ALLOC_ERROR);
	ft_lstadd_back(args, popFirst(token));
	(*c)->label = (char*)(*args)->content; // getting the pointer to the first arg as the label
	return (0);
}

static int		parse_args(t_list **token, t_list **args, t_list **redir)
{
	char	*t;

	*redir = 0;
	while (*token && !is_operator((t = getToken(token))))
	{
		if (ft_strncmp(t, ">", 2) == 0 || ft_strncmp(t, ">>", 2) == 0 || ft_strncmp(t, "<", 2) == 0)
		{
			if (joinTokens(token, redir) == ALLOC_ERROR)
				return (ALLOC_ERROR);
		}
		else
			ft_lstadd_back(args, popFirst(token)); // it calls nextToken() in any case
	}
	return (0);
}

int		parse_cmd(t_list **token, t_cmd **c)
{
	int		r;
	t_list *args;
	t_list *redir;

	if (!*token || is_operator(getToken(token)))
		return (PARSING_ERROR);
	if (parse_label(&args, c, token) == ALLOC_ERROR)
		return (ALLOC_ERROR);
	r = parse_args(token, &args, &redir);
	if (r == ALLOC_ERROR)
		return (ALLOC_ERROR);
	(*c)->args = list_to_char_array(args);
	(*c)->redir = list_to_char_array(redir);
	if ((ft_lstsize(args) && (*c)->args == 0) ||
		(ft_lstsize(redir) && (*c)->redir == 0))
		return (ALLOC_ERROR);
	ft_lstclear(&args, 0);
	ft_lstclear(&redir, 0);
	return (0);
}
