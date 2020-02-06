/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:05:10 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/04 17:06:14 by mclaudel         ###   ########.fr       */
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

void	free_node(t_node *tofree)
{
	if (tofree->left)
		free_node(tofree->left);
	if (tofree->right)
		free_node(tofree->left);
	free(tofree);
}

void	print_node(t_node *n, int level)
{
	int i = 0;
	
	if (!n)
		return ;
	if (n->right)
		print_node(n->right, level + 1);
	printf("\n");
	while (i < level)
	{
		printf("\t");
		i++;
	}
	if (n->type == OR)
		printf("||\n");
	if (n->type == AND)
		printf("&&\n");
	if (n->type == PIPELINE)
		printf("pi\n");
	printf("\n");
	if (n->left)
		print_node(n->left, level + 1);
}

void	print_tree(t_node *n)
{
	if (!n)
	{
		printf ("NUL NUL NUL\n");
		return ;
	}
	print_node(n->right, 1);
	if (n->type == OR)
		printf("||\n");
	if (n->type == AND)
		printf("&&\n");
	if (n->type == PIPELINE)
		printf("pi\n");
	print_node(n->left, 1);
}
