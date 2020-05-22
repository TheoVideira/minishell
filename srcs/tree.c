/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:05:10 by mclaudel          #+#    #+#             */
/*   Updated: 2020/03/12 11:33:27 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*create_node(t_nodetype t, void *obj)
{
	t_node *ptr;

	ptr = ft_calloc(1, sizeof(t_node));
	if (!ptr)
		return (0);
	ptr->type = t;
	ptr->obj = obj;
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

void	print_subarr(char **subl, char *label)
{
	int i;

	if (!subl)
		return ;
	printf ("%s", label);
	printf ("(");
	i = 0;
	while (subl[i])
	{
		if (subl[i + 1])
			printf("%s, ", subl[i]);
		else
			printf("%s", subl[i]);
		i++;
	}
	printf (") ");
}

void	print_pipeline(t_pipeline *p)
{
	t_list	*l;
	t_cmd	*c;

	l = p->cmds;
	while (l)
	{
		c = (t_cmd*)l->content;
		printf ("%s ", c->label);
		print_subarr(c->args, "ar");
		print_subarr(c->redir, "r");
		l = l->next;
		if (l)
			printf (" | ");
	}
}

void	print_entry(t_entry *entry, int level)
{
	t_list	*l;

	(void) level;
	l = entry->instructions;
	printf (" ENTRY ");
	while (l)
	{
		print_node((t_node*)l->content, level + 1);
		l = l->next;
		
		// printf (" E ");
	}
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
		print_pipeline((t_pipeline*)n->obj);
	if (n->type == ENTRY)
		print_entry((t_entry*)n->obj, level + 1);
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
	print_node(n, 0);
}
