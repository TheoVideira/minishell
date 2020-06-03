/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:54:00 by user42            #+#    #+#             */
/*   Updated: 2020/06/03 03:18:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	g_mini.lastcall = 130;
	if (!g_mini.childs)
		write(1, "\n\e[1;35mOK-BOOMER\e[0m$>", 24);
	brutally_murder_childrens(sig);
}

void	handle_sigquit(int sig)
{
	brutally_murder_childrens(sig);
	g_mini.lastcall = 131;
}
