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

int		double_quotes(char *str, char **token,  t_minishell *mini)
{
	int		size;

	size = 0;
	while (*str && *str != '"')
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1)); // CHECK ALLOC
	ft_memcpy(*token, str - size, size);
	replace_env(token, mini); // check error
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
	*token = ft_calloc(1, sizeof(char) * (size + 1)); // CHECK ALLOC
	ft_memcpy(*token, str - size, size);
	return (size);
}

int		no_quotes(char *str, char **token,  t_minishell *mini)
{
	int		size;

	size = 0;
	while (*str && !ft_isspace(*str) && *str != '"' && *str != '\'' && !is_separator(str))
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1)); // CHECK ALLOC
	ft_memcpy(*token, str - size, size);
	replace_env(token, mini); // check error
	return (size);
}
