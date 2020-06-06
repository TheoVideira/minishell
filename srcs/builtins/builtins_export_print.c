/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 02:49:01 by user42            #+#    #+#             */
/*   Updated: 2020/06/06 19:39:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	builtin_export_tri(t_dict *env, int *tab)
{
	int i;
	int t;
	int tmp;

	i = -1;
	while (++i < ft_dictsize(env))
		tab[i] = i;
	t = 0;
	while (!t)
	{
		i = -1;
		t = 1;
		while (++i < ft_dictsize(env) - 1)
			if (ft_strcmp(ft_dictgetindex(env, tab[i])->key,
				ft_dictgetindex(env, tab[i + 1])->key) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				t = 0;
			}
	}
}

int			builtin_export_print(t_dict *env)
{
	int		i;
	int		tab[ft_dictsize(env)];
	t_dict	*var;

	builtin_export_tri(env, tab);
	i = -1;
	while (++i < ft_dictsize(env))
	{
		var = ft_dictgetindex(env, tab[i]);
		if (strcmp(var->key, "_") == 0)
			continue ;
		write(1, "declare -x ", 11);
		write(1, var->key, ft_strlen(var->key));
		if (!var->value)
		{
			write(1, "\n", 1);
			continue;
		}
		write(1, "=\"", 2);
		write(1, var->value, strlen(var->value));
		ft_putendl_fd("\"", 1);
	}
	return (0);
}
