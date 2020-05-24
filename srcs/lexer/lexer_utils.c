#include <minishell.h>

int		is_separator(char *str)
{
	if (*str == '&' && *(str + 1) == '&')
		return (2);
	if (*str == '|' && *(str + 1) == '|')
		return (2);
	if (*str == '>' && *(str + 1) == '>') // multi line
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
