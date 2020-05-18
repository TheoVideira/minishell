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
	char	*token;
	char	*start;
	char	*tokenstart;
	int		tmp;

	(void)mini;
	start = str;
	while (ft_isspace(*str))
		str++;
	tokenstart = str;
	while (*str && !ft_isspace(*str))
	{
		if ((tmp = is_separator(str)))
		{
			str += tmp;
			break;
		}	
		else if (*str == '"')
			str += 1 + loop_until(str + 1, '"') + 1; // check error
		else if (*str == '\'')
			str += 1 + loop_until(str + 1, '\'') + 1; // check error
		else
			str++;
		if (is_separator(str))
			break ;
		//check uneven quotes
	}
	if (str - tokenstart == 0)
	{
		token = 0;
		return (0);
	}
	else if (!(token = handle_separators(tokenstart)))
	{
		token = ft_calloc(1, sizeof(char) * (str - tokenstart + 1)); // check error
		ft_memcpy(token, tokenstart, str - tokenstart);
	}
	*tofill = token;
	return ((unsigned int)(tokenstart - start + ft_strlen(token)));
}

t_list	*tokenize(char *str, t_minishell *mini)
{
	t_list	*tokens;
	t_list	*new;
	char	*token;
	int		tmp;

	tokens = 0;
	while ((tmp = get_next_token(str, &token, mini)))
	{
		//check tmp value ?
		if (!(new = ft_lstnew(token)))
			return (0);
		ft_lstadd_back(&tokens, new); // check for new null
		str += tmp;
	}
	return (tokens);
}
