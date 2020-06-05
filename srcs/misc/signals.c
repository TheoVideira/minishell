/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:54:00 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 17:14:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	g_mini.lastcall = 130;
	if (!g_mini.childs)
		write(1, "\n\e[1;35mOK-BOOMER\e[0m$>", 24);
	else
		write(1, "\n", 1);
	brutally_murder_childrens(sig);
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
