/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:32:27 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/03 15:50:17 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void			free_tokenarray(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
