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

int			get_next_token(char *str, char **tofill,  t_minishell *mini)
{
	char *token;
	char *subtoken;
	char *tmp;
	char *start;

	token = ft_calloc(1, 1); // check if null or redo strjoin to handle null
	start = str;
	while (ft_isspace(*str))
		str++;
	while (*str && !ft_isspace(*str))
	{
		if ((subtoken = handle_separators(str)))
			str += ft_strlen(subtoken);
		else if (*str == '"')
			str += double_quotes(str, &subtoken, mini); // check error
		else if (*str == '\'')
			str += single_quotes(str, &subtoken); // check error
		else
			str += no_quotes(str, &subtoken, mini);
		tmp = token;
		token = ft_strjoin(token, subtoken);
		free(tmp);
		free(subtoken);
		if (is_separator(str) || is_separator(token))
			break ;
	}
	*tofill = token;
	return ((unsigned int)(str - start));
}

t_list	*tokenize(char *str, t_minishell *mini)
{
	t_list	*tokens;
	char	*token;
	int		tmp;

	tokens = 0;
	while ((tmp = get_next_token(str, &token, mini)))
	{
		ft_lstadd_back(&tokens, ft_lstnew(token)); // check for new null
		str += tmp;
	}
	return (tokens);
}
