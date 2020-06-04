/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_formatting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:01:53 by user42            #+#    #+#             */
/*   Updated: 2020/06/04 23:30:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		double_quotes(char *str, char **token)
{
	int		size;
	int		r;

	size = 0;
	while (*str)
	{
		if (*str == '\\' && str++)
			size++;
		else if (*str == '"')
			break ;
		size++;
		str++;
	}
	if ((*token = ft_calloc(1, sizeof(char) * (size + 1))) == 0)
		return (ALLOC_ERROR);
	ft_memcpy(*token, str - size, size);
	if ((r = replace_env(token))
		|| (r = replace_escaped(token, 1)))
	{
		free(*token);
		return (r);
	}
	return (size);
}

static int		single_quotes(char *str, char **token)
{
	int		size;

	size = 0;
	while (*str)
	{
		if (*str == '\'')
			break ;
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1));
	if (*token == 0)
		return (ALLOC_ERROR);
	ft_memcpy(*token, str - size, size);
	return (size);
}

static int		no_quotes(char *str, char **token)
{
	int		size;
	int		r;

	size = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"'
			|| ft_isspace(*str)) && *(str - 1) != '\\')
			break ;
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1));
	if (*token == 0)
		return (ALLOC_ERROR);
	ft_memcpy(*token, str - size, size);
	r = replace_env(token);
	if (r || (r = replace_escaped(token, 0)))
	{
		free(*token);
		return (r);
	}
	return (size);
}

static int		read_subtoken(char *arg, char **subtoken, char *token)
{
	int r;
	int quote;

	quote = 0;
	if (*arg == '"' && (quote = 1))
		r = double_quotes(arg + 1, subtoken);
	else if (*arg == '\'' && (quote = 1))
		r = single_quotes(arg + 1, subtoken);
	else
		r = no_quotes(arg, subtoken);
	if (r < 0)
	{
		if (r != ALLOC_ERROR)
			free(subtoken);
		free(token);
		return (r);
	}
	return (r + quote * 2);
}

int				format_arg(char *arg, char **into)
{
	char	*token;
	char	*subtoken;
	char	*tmp;
	int		r;

	if ((token = ft_calloc(1, 1)) == 0)
		return (0);
	while (ft_isspace(*arg))
		arg++;
	while (*arg && !ft_isspace(*arg))
	{
		if ((r = read_subtoken(arg, &subtoken, token)) < 0)
			return (r);
		arg += r;
		tmp = token;
		token = ft_strjoin(token, subtoken);
		free(tmp);
		free(subtoken);
		if (!token)
			return (ALLOC_ERROR);
	}
	*into = token;
	return (0);
}
