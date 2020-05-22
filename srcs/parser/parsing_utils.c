#include <minishell.h>

int		is_operator(char *str)
{
	if (*str == '&' && *(str + 1) == '&')
		return (2);
	if (*str == '|' && *(str + 1) == '|')
		return (2);
	if (*str == '(' && *(str + 1) == '\0')
		return (1);
	if (*str == ')' && *(str + 1) == '\0')
		return (1);
	if (*str == '|' && *(str + 1) == '\0')
		return (1);
	if (*str == ';' && *(str + 1) == '\0')
		return (1);
	return (0);
}