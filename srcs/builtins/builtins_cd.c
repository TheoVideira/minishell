/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:21:45 by marvin            #+#    #+#             */
/*   Updated: 2020/06/05 22:21:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dict	*ft_get_pwd(char *keyname)
{
	char *key;
	char *value;

	if (!(key = ft_strdup(keyname)))
		return (NULL);
	if (!(value = getcwd(NULL, 0)))
	{
		free(key);
		return (NULL);
	}
	return (ft_dictnew(key, value));
}

static int		cd_return(char *dir, t_dict *oldpwd, t_dict *pwd)
{
	ft_perror("minishell", "cd", dir);
	if (oldpwd)
		ft_dictrem(&oldpwd, "OLDPWD", free);
	if (pwd)
		ft_dictrem(&pwd, "PWD", free);
	return (1);
}

int				builtin_cd(int ac, char *const *av, t_dict *env)
{
	char	*dir;
	t_dict	*oldpwd;
	t_dict	*pwd;

	oldpwd = NULL;
	pwd = NULL;
	if (ac > 2)
	{
		ft_perror_msg("minishell", "cd", NULL, "too many arguments");
		return (1);
	}
	dir = (ac == 1) ? ft_dictget(env, "HOME") : av[1];
	if (!(oldpwd = ft_get_pwd("OLDPWD")))
		return (cd_return(dir, oldpwd, pwd));
	if (chdir(dir))
		return (cd_return(dir, oldpwd, pwd));
	if (!(pwd = ft_get_pwd("PWD")))
		return (cd_return(dir, oldpwd, pwd));
	ft_dictrem(&env, "OLDPWD", free);
	ft_dictadd(&env, oldpwd);
	ft_dictrem(&env, "PWD", free);
	ft_dictadd(&env, pwd);
	return (0);
}
