/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_formatting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:01:53 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 14:01:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		double_quotes(char *str, char **token)
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
	replace_env(token); // check error
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

int		no_quotes(char *str, char **token)
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
	replace_env(token); // check error
	return (size);
}

char		*format_arg(char *arg)
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
			arg += 1 + double_quotes(arg + 1, &subtoken); // check error
		else if (*arg == '\'')
			arg += 1 + single_quotes(arg + 1, &subtoken); // check error
		else
			arg += no_quotes(arg, &subtoken);
		tmp = token;
		token = ft_strjoin(token, subtoken); // check error
		free(tmp);
		free(subtoken);
	}
	return (token);
}