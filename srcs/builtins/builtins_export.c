/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:56:12 by marvin            #+#    #+#             */
/*   Updated: 2020/05/22 19:04:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void builtin_export_tri(t_dict *env, int *tab)
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

static int  builtin_export_print(t_dict *env)
{
   	int     i;
    int     tab[ft_dictsize(env)];
    t_dict  *var;

    builtin_export_tri(env, tab);
    i = -1;
    while(++i < ft_dictsize(env))
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

static int  builtin_export_add(int ac, char* const* av, t_dict *env)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

    i = 0;
	while (++i < ac)
	{
		if ((eq = ft_strchr(av[i], '=')))
		{
			*eq = 0;
			ft_dictrem(&env, av[i], free);
			key = ft_strdup(av[i]);
			value = ft_strdup(eq + 1);
			ft_dictadd(&env, ft_dictnew(key, value));
		}
        else
        {
	    	ft_dictrem(&env, av[i], free);
		    ft_dictadd(&env, ft_dictnew(ft_strdup(av[i]), NULL));
        }
    }
	return(0);
}

int         builtin_export(int ac, char* const* av, t_dict *env)
{
	if (ac == 1)
		return (builtin_export_print(env));
	else
        return (builtin_export_add(ac, av, env));
}


