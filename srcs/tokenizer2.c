#include <minishell.h>

int		is_separator(char *str)
{
	if (*str == '&' && *(str + 1) == '&')
		return (2);
	if (*str == '|' && *(str + 1) == '|')
		return (2);
	if (*str == '>' && *(str + 1) == '>')
		return (2);
	if (*str == '(')
		return (1);
	if (*str == ')')
		return (1);
	if (*str == '|')
		return (1);
	if (*str == ';')
		return (1);
	if (*str == '<')
		return (1);
	if (*str == '>')
		return (1);
	return (0);
}

int		double_quotes(char *str, char **token)
{
	int		size;

	size = 0;
	while (*str && *str != '"')
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1));
	ft_memcpy(*token, str - size, size);
	//replace stuff
	return (size);
}

int		single_quotes(char *str, char **token)
{
	int		size;

	size = 0;
	while (*str && *str != '\'')
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1));
	ft_memcpy(*token, str - size, size);
	return (size);
}

int		no_quotes(char *str, char **token)
{
	int		size;

	size = 0;
	while (*str && !ft_isspace(*str) && *str != '"' && *str != '\'' && !is_separator(str))
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1));
	ft_memcpy(*token, str - size, size);
	//replace stuff
	return (size);
}