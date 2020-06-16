/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 04:59:21 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 03:29:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	run_entry(t_entry *entry)
{
	t_list	*tree;
	int		r;

	tree = entry->instructions;
	r = 0;
	while (tree)
	{
		r = run_tree((t_node *)tree->content);
		if (r == ALLOC_ERROR)
			alloc_error();
		tree = tree->next;
	}
	return (0);
}
