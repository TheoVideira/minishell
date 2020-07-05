/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 01:00:02 by user42            #+#    #+#             */
/*   Updated: 2020/07/06 01:22:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	need_backslash(char c)
{
	return (c == '$' || c == '\\' || c == '"');
}

int			how_many_skips(char *s)
{
	int i;
	int d;

	i = -1;
	d = 0;
	while (s[++i])
	{
		if (need_backslash(s[i]))
			d++;
	}
	return (d);
}

void		create_value(char *eq, char **value)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (eq[++i])
	{
		if (need_backslash(eq[i]))
		{
			value[0][j] = '\\';
			j++;
		}
		value[0][j] = eq[i];
		j++;
	}
	value[0][j] = 0;
}
