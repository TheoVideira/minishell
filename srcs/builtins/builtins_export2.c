/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:59:12 by marvin            #+#    #+#             */
/*   Updated: 2020/06/04 16:07:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int var_exists(char *eq, char *key)
{
    if (!eq && ft_dictget(g_mini->env, key))
    {
        free(key);
        return(0);
    }
    return (1);
}