/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:44:30 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 21:11:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		string_arr_size(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i);
}

char	**list_to_char_array(t_list *l)
{
	size_t	s;
	char	**arr;
	int		i;

	if (!l)
		return (0);
	s = ft_lstsize(l);
	if (!(arr = ft_calloc(1, sizeof(char*) * (s + 1))))
		return (0);
	i = 0;
	while (l)
	{
		arr[i] = (char*)l->content;
		i++;
		l = l->next;
	}
	return (arr);
}

int		is_only_space(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
