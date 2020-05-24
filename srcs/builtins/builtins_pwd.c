/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:15:02 by marvin            #+#    #+#             */
/*   Updated: 2020/05/24 19:15:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_pwd(void)
{
	char *path;

	if (!(path = getcwd(NULL, 0)))
		ft_perror("minishell", "pwd", NULL);
	write(1, path, ft_strlen(path));
	free(path);
	return (0);
}
