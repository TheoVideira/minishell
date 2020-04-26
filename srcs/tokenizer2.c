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

int		replace_env(char **str, t_minishell *mini)
{
	char *ptr;
	char *start;
	char *varkey;
	char *varvalue;
	char *new;
	char *tofree;

	new = *str;
	ptr = new;
	while (*ptr)
	{
		if (*ptr == '$')
		{
			start = ptr;
			if (*(++ptr) == '?')
			{
				(void) ptr;

				tofree = new;
				varvalue = ft_itoa(mini->lastcall); // check env
				printf("%d\n", mini->lastcall);
				new = ft_strreplace(new, start - new, 2, varvalue); // Check error
				//Couilles TO DO
			}
			
			else
			{
				while (*ptr && !ft_isspace(*ptr) && *ptr != '$' && !is_separator(ptr))
					ptr++;
				varkey = ft_substr(new, start - new + 1, ptr - start - 1); // check error
				if (!(varvalue = (char*)ft_dictget(mini->env, varkey)))
					varvalue = "";
				tofree = new;
				new = ft_strreplace(new, start - new, ft_strlen(varkey) + 1, varvalue); // Check error
			}
			free(tofree);
			ptr = new;
		}
		else
			ptr++;
	}
	*str = new;
	return (0);
}