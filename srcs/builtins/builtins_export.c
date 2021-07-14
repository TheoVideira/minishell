/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:38:35 by marvin            #+#    #+#             */
/*   Updated: 2020/06/05 02:49:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_export(int ac, char *const *av, t_dict *env)
{
	if (ac == 1)
		return (builtin_export_print(env));
	else
		return (builtin_export_add(ac, av, env));
}
