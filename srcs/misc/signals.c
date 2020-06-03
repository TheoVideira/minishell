/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:54:00 by user42            #+#    #+#             */
/*   Updated: 2020/06/03 02:12:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	brutally_murder_childrens(sig);
	g_mini.lastcall = 130;
}

void	handle_sigquit(int sig)
{
	brutally_murder_childrens(sig);
	g_mini.lastcall = 131;
}
