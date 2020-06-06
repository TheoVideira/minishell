/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:14:42 by marvin            #+#    #+#             */
/*   Updated: 2020/06/06 19:42:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_key(char *key)
{
	int i;
	int nan;

	i = -1;
	nan = 0;
	if (!key)
		return (0);
	while (key[++i])
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
		{
			if (ft_isalpha(key[i]) || key[i] == '_')
				nan = 1;
			if (!i && ft_isdigit(key[i]))
				return (0);
		}
		else
			return (0);
	}
	return ((!i || !nan) ? 0 : 1);
}

static int	is_skippable(char *key, int *ret)
{
	if (!valid_key(key) || (key[0] == '_' && !key[1]))
	{
		if (!(key[0] == '_' && !key[1]))
			ft_perror_msg("minishell", "export", key,
				"not a valid identifier");
		*ret = 1;
		return (1);
	}
	return (0);
}

int			builtin_unset(int ac, char *const *av, t_dict *env)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (++i < ac)
	{
		if (is_skippable(av[i], &ret))
			continue;
		ft_dictrem(&env, av[i], free);
	}
	return (ret);
}
