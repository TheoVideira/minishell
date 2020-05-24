/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:11:43 by marvin            #+#    #+#             */
/*   Updated: 2020/05/24 17:12:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cd(int ac, char* const* av, t_dict* env)
{
	char *dir;
	char *oldpwd;
	char *key;

	oldpwd = NULL;
	if (ac > 2)
		return (1);
	if (!(key = ft_strdup("OLDPWD")) || !(oldpwd = getcwd(NULL, 0)))
	{
		ft_perror("minishell", "cd", NULL);
		free(key);
		free(oldpwd);
		return (1);
	}
	dir = (ac == 1) ? ft_dictget(env, "HOME") : av[1];
	if (chdir(dir))
	{
		ft_perror("minishell", "cd", dir);
		free(key);
		free(oldpwd);
		return (1);
	}
	ft_dictrem(&env, "OLDPWD", free);
	ft_dictadd(&env, ft_dictnew(key, oldpwd));
	return (0);
}
