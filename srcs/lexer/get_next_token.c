/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:02:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/01 19:19:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	loop_until(char *str, char end)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == end && str[i - 1] != '\\')
			break ;
		i++;
	}
	printf("HERE TOO\n");
	if (!str[i])
		return (QUOTE_NOT_CLOSED);
	printf("asdsad HERE TOO\n");
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
		if (*str == '\\')
		{
			r = (*(str + 1) != 0); 
			str += 1 + r;
			len += 1 + r;
		}
		else if ((*str == '\'' || *str == '"') && ((*str - 1) != '\\' || len == 0))
		{
			if ((r = loop_until(str + 1, *str)) < 0)
				return (r);
			str += 1 + r + 1;
			len += 1 + r + 1;
		}
		else
		{
			len++;
			str++;
		}
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
