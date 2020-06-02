/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:02:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 04:56:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	single_quotes(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '\'')
			return (i + 1);
		i++;
	}
	return (QUOTE_NOT_CLOSED);
}

static int	double_quotes(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '"')
			return (i + 1);
		i++;
	}
	return (QUOTE_NOT_CLOSED);
}

static int	no_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (is_separator(&str[i]) && str[i - 1] != '\\')
			break ;
		if ((str[i] == '\'' || str[i] == '"'
			|| ft_isspace(str[i])) && str[i - 1] != '\\')
			break ;
		i++;
	}
	return (i);
}

static int	read_token(char *str)
{
	int		len;
	int		r;

	len = 0;
	if (*str && (r = is_separator(str)))
		return (r);
	while (*str && !ft_isspace(*str))
	{
		if (is_separator(str))
			break ;
		else if (*str == '\'')
			r = single_quotes(str);
		else if (*str == '"')
			r = double_quotes(str);
		else
			r = no_quotes(str);
		if (r < 0)
			return (r);
		len += r;
		str += r;
	}
	return (len);
}

int			get_next_token(char *str, char **tofill)
{
	char	*token;
	char	*start;
	char	*tokenstart;
	int		r;

	start = str;
	while (ft_isspace(*str))
		str++;
	tokenstart = str;
	if ((r = read_token(str)) < 0)
		return (r);
	str += r;
	if (str - tokenstart == 0)
	{
		token = 0;
		return (0);
	}
	if (!(token = ft_calloc(1, sizeof(char) * (str - tokenstart + 1))))
		return (ALLOC_ERROR);
	ft_memcpy(token, tokenstart, str - tokenstart);
	*tofill = token;
	return ((unsigned int)(tokenstart - start + ft_strlen(token)));
}
