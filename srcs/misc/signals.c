/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:54:00 by user42            #+#    #+#             */
/*   Updated: 2020/06/19 00:29:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	int r;

	if (!g_mini.childs)
		r = write(1, "\n\e[1;35mOK-BOOMER\e[0m$>", 24);
	else
		r = write(1, "\n", 1);
	if (r == -1)
		fatal_error("write");
	brutally_murder_childrens(sig);
	g_mini.lastcall = 130;
}

void	handle_sigquit(int sig)
{
	if (g_mini.childs)
	{
		brutally_murder_childrens(sig);
		ft_putstr_fd("Quit (core dumped)\n", 1);
	}
	else
		ft_putstr_fd("\b\b  \b\b", 1);
	g_mini.lastcall = 131;
}
