#include <minishell.h>

char	**list_to_char_array(t_list *l)
{
	size_t s;
	char **arr;
	int i;

	if (!l)
		return (0);
	s = ft_lstsize(l);
	if (!(arr = ft_calloc(1, sizeof(char*) * (s + 1))))
		return (0);
	i = 0;
	while (l)
	{
		arr[i] = (char*) l->content;
		i++;
		l = l->next;
	}
	return (arr);
}



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