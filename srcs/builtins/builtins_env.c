/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:13:35 by marvin            #+#    #+#             */
/*   Updated: 2020/05/30 15:26:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_dict *env)
{
	while (env)
	{
		if (env->value)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
