/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:56:12 by marvin            #+#    #+#             */
/*   Updated: 2020/06/03 15:30:56 by user42           ###   ########.fr       */
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

static int	builtin_export_print(t_dict *env)
{
	int		i;
	int		tab[ft_dictsize(env)];
	t_dict	*var;

	builtin_export_tri(env, tab);
	i = -1;
	while (++i < ft_dictsize(env))
	{
		var = ft_dictgetindex(env, tab[i]);
		write(1, "declare -x ", 11);
		write(1, var->key, ft_strlen(var->key));
		if (!var->value)
		{
			write(1, "\n", 1);
			continue;
		}
		write(1, "=", 1);
		ft_putendl_fd(var->value, 1);
	}
	return (0);
}

static int	builtin_export_add(int ac, char *const *av, t_dict *env)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

	i = 0;
	while (++i < ac)
	{
		if ((eq = ft_strchr(av[i], '=')) == NULL)
			continue ;
		key = (eq) ? ft_substr(av[i], 0, eq - av[i]) : ft_strdup(av[i]);
		if (!valid_key(key) || (key[0] == '_' && !key[1]))
		{
			if (!(key[0] == '_' && !key[1]))
				ft_perror_msg("-minishell", "export", key,
					"not a valid identifier");
			free(key);
			continue;
		}
		value = ft_strdup(eq + 1);
		ft_dictrem(&env, key, free);
		ft_dictadd(&env, ft_dictnew(key, value));
	}
	return (0);
}

int			builtin_export(int ac, char *const *av, t_dict *env)
{
	if (ac == 1)
		return (builtin_export_print(env));
	else
		return (builtin_export_add(ac, av, env));
}
