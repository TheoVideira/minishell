/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:15:02 by marvin            #+#    #+#             */
/*   Updated: 2020/06/04 15:51:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_pwd(void)
{
	char *path;

	if (!(path = getcwd(NULL, 0)))
		ft_perror("minishell", "pwd", NULL);
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
