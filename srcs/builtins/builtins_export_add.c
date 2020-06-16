/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_add.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:59:12 by marvin            #+#    #+#             */
/*   Updated: 2020/06/05 03:12:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_exists(char *eq, char *key)
{
	if (!eq && ft_dictget(g_mini.env, key))
	{
		free(key);
		return (0);
	}
	return (1);
}

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

static int	is_skippable(char *key, char *eq)
{
	if (!valid_key(key) || (key[0] == '_' && !key[1]))
	{
		if (!(key[0] == '_' && !key[1]))
			ft_perror_msg("minishell", "export", key,
				"not a valid identifier");
		free(key);
		return (1);
	}
	if (!var_exists(eq, key))
		return (1);
	return (0);
}

static int	compute_value(char *key, char *eq, char **value)
{
	if (eq)
	{
		*value = ft_strdup(eq + 1);
		if ((*value) == NULL)
		{
			free(key);
			ft_perror("minishell", "export", 0);
			return (1);
		}
	}
	else
		*value = NULL;
	return (0);
}

int			builtin_export_add(int ac, char *const *av, t_dict *env)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

	i = 0;
	while (++i < ac)
	{
		eq = ft_strchr(av[i], '=');
		key = (eq) ? ft_substr(av[i], 0, eq - av[i]) : ft_strdup(av[i]);
		if (key == NULL)
		{
			ft_perror("minishell", "export", 0);
			return (1);
		}
		if (is_skippable(key, eq))
			continue ;
		if (compute_value(key, eq, &value))
			return (1);
		ft_dictrem(&env, key, free);
		ft_dictadd(&env, ft_dictnew(key, value));
	}
	return (0);
}
