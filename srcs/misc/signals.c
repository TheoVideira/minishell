/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:54:00 by user42            #+#    #+#             */
/*   Updated: 2020/07/06 16:06:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	int r;

	(void)sig;
	if (!g_mini.childs)
	{
		brutally_murder_childrens(sig);
		r = write(1, "\n\e[1;35mOK-BOOMER\e[0m$>", 24);
		if (r == -1)
			fatal_error("write");
	}
	g_mini.lastcall = 130;
}

void	handle_sigquit(int sig)
{
	if (g_mini.childs)
	{
		brutally_murder_childrens(sig);
		g_mini.lastcall = 131;
	}
}
