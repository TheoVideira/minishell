/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_formatting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:02:14 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 23:10:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		is_valid_char(char c)
{
	return (c
			&& !ft_isspace(c)
			&& (ft_isalnum(c) || c == '_'));
}

static int		replace_last_call(char **new, char *start)
{
	char *tofree;
	char *varvalue;

	tofree = *new;
	varvalue = ft_itoa(g_mini.lastcall);
	if (varvalue == 0)
		return (ALLOC_ERROR);
	*new = ft_strreplace(*new, start - *new, 2, varvalue);
	if (*new == 0)
	{
		free(varvalue);
		return (ALLOC_ERROR);
	}
	free(varvalue);
	free(tofree);
	return (0);
}

static int		replace_env_value(char **new, char *ptr, char *start)
{
	char *tofree;
	char *varkey;
	char *varvalue;

	while (is_valid_char(*ptr))
		ptr++;
	varkey = ft_substr(*new, start - *new + 1, ptr - start - 1);
	if (!varkey)
		return (ALLOC_ERROR);
	if (!(varvalue = (char*)ft_dictget(g_mini.env, varkey)))
		varvalue = "";
	tofree = *new;
	*new = ft_strreplace(*new, start - *new,
					ft_strlen(varkey) + 1, varvalue);
	free(varkey);
	free(tofree);
	if (!new)
		return (ALLOC_ERROR);
	return (0);
}

int				replace_env(char **str)
{
	char	*ptr;
	char	*start;
	int		r;

	ptr = *str;
	while (*ptr)
		if (*ptr == '$'
			&& (ptr == *str || (ptr != *str && *(ptr - 1) != '\\')))
		{
			start = ptr;
			if (*(++ptr) == '?')
				r = replace_last_call(str, start);
			else
				r = replace_env_value(str, ptr, start);
			if (r)
				return (r);
			ptr = *str;
		}
		else
			ptr++;
	return (0);
}
