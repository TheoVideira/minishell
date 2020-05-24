#include <minishell.h>

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
	while (*str && !ft_isspace(*str) && *str != '"' && *str != '\'')
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1)); // CHECK ALLOC
	ft_memcpy(*token, str - size, size);
	replace_env(token, mini); // check error
	return (size);
}

char		*format_arg(char *arg,  t_minishell *mini)
{
	char *token;
	char *subtoken;
	char *tmp;

	token = ft_calloc(1, 1); // check if null or redo strjoin to handle null
	while (ft_isspace(*arg))
		arg++;
	while (*arg && !ft_isspace(*arg))
	{
		if (*arg == '"')
			arg += 1 + double_quotes(arg + 1, &subtoken, mini); // check error
		else if (*arg == '\'')
			arg += 1 + single_quotes(arg + 1, &subtoken); // check error
		else
			arg += no_quotes(arg, &subtoken, mini);
		tmp = token;
		token = ft_strjoin(token, subtoken); // check error
		free(tmp);
		free(subtoken);
	}
	return (token);
}