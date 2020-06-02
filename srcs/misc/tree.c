/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:05:10 by mclaudel          #+#    #+#             */
/*   Updated: 2020/06/02 23:37:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*create_node(t_nodetype t, t_pipeline *p)
{
	t_node *ptr;

	ptr = ft_calloc(1, sizeof(t_node));
	if (!ptr)
		return (0);
	ptr->type = t;
	ptr->pipeline = p;
	return (ptr);
}

t_node	*create_node_trio(t_nodetype t, t_node *left, t_node *right)
{
	t_node *ptr;

	if (!left && !right)
		return (0);
	if (left && !right)
		return (left);
	if (right && !left)
		return (right);
	ptr = create_node(t, 0);
	if (!ptr)
		return (0);
	ptr->left = left;
	ptr->right = right;
	return (ptr);
}
