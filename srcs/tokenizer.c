#include <minishell.h>

char		*handle_separators(char *str)
{
	if (*str == '&' && *(str + 1) == '&')
		return (ft_strdup("&&"));
	if (*str == '|' && *(str + 1) == '|')
		return (ft_strdup("||"));
	if (*str == '>' && *(str + 1) == '>')
		return (ft_strdup(">>"));
	if (*str == '(')
		return (ft_strdup("("));
	if (*str == ')')
		return (ft_strdup(")"));
	if (*str == '|')
		return (ft_strdup("|"));
	if (*str == ';')
		return (ft_strdup(";"));
	if (*str == '<')
		return (ft_strdup("<"));
	if (*str == '>')
		return (ft_strdup(">"));
	return (0);
}


int			loop_until(char *str, char end) // might handle multiline
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == end && str[i - 1] != '\\') // unspecify
			return (i);
		i++;
	}
	return (i);
}

int			get_next_token(char *str, char **tofill,  t_minishell *mini)
{
	char *token;
	char *start;
	char *tokenstart;

	(void)mini;
	start = str;
	while (ft_isspace(*str))
		str++;
	tokenstart = str;
	while (*str && !ft_isspace(*str))
	{
		if (is_separator(str))
			break;
		else if (*str == '"')
			str += 1 + loop_until(str + 1, '"') + 1; // check error
		else if (*str == '\'')
			str += 1 + loop_until(str + 1, '\'') + 1; // check error
		else
			str++;
		//check uneven quotes
	}
	if (str - tokenstart == 0)
	{
		token = 0;
		return (0);
	}
	else if (!(token = handle_separators(str)))
	{
		token = ft_calloc(1, sizeof(char) * (str - tokenstart + 1));
		ft_memcpy(token, tokenstart, str - tokenstart);
	}
	*tofill = token;
	return ((unsigned int)(tokenstart - start + ft_strlen(token)));
}

t_list	*tokenize(char *str, t_minishell *mini)
{
	t_list	*tokens;
	char	*token;
	int		tmp;

	tokens = 0;
	while ((tmp = get_next_token(str, &token, mini)))
	{
		printf("tmp %d\n", tmp);
		ft_lstadd_back(&tokens, ft_lstnew(token)); // check for new null
		str += tmp;
	}
	printf("tmp last %d\n", tmp);
	return (tokens);
}
