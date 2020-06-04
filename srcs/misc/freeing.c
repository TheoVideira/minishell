/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:32:27 by mclaudel          #+#    #+#             */
/*   Updated: 2020/06/02 01:48:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_char_array(char **arr)
{
	char **ptr;

	ptr = arr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(arr);
}

void	free_node(t_node *tofree)
{
	if (tofree->left)
		free_node(tofree->left);
	if (tofree->right)
		free_node(tofree->right);
	if (tofree->type == PIPELINE)
		free_pipeline(tofree->pipeline);
	free(tofree);
}

void	free_entry(t_entry *e)
{
	ft_lstclear(&e->instructions, (void (*)(void *))free_node);
	free(e);
}

void	free_pipeline(t_pipeline *p)
{
	ft_lstclear(&p->cmds, (void (*)(void *))free_command);
	free(p);
}

void	free_command(t_cmd *c)
{
	free_char_array(c->args);
	if (c->redir)
		free_char_array(c->redir);
	free(c);
}
