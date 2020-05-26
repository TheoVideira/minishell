/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:55:20 by user42            #+#    #+#             */
/*   Updated: 2020/05/26 15:55:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	run_tree(t_node *tree)
{
	if (tree->type == PIPELINE)
		return (run_pipeline(tree->pipeline));
	if (tree->type == OR)
		return (!(run_tree(tree->left) == 0 || run_tree(tree->right) == 0));
	if (tree->type == AND)
		return (!(run_tree(tree->left) == 0 && run_tree(tree->right) == 0));
	return (0);
}
