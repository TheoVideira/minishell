/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:25 by mclaudel          #+#    #+#             */
/*   Updated: 2020/06/05 21:39:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_memjoin(char const *s1, int l1, char const *s2, int l2)
{
	char	*str;
	char	*ptr;

	if (!(str = malloc(l1 + l2 + 1)))
		return (0);
	ptr = str;
	if (l1)
		while (l1--)
			*ptr++ = *s1++;
	if (l2)
		while (l2--)
			*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

int			endofline(char *str, int len)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (++i < len)
		if (str[i] == '\n' || str[i] == '\0')
			return (i);
	return (-1);
}

t_gnllst	*ft_lstgnlnew(int fd)
{
	t_gnllst *el;

	if (!(el = malloc(sizeof(t_gnllst))))
		return (NULL);
	el->fd = fd;
	el->charsleft = 0;
	el->size = 0;
	el->next = 0;
	return (el);
}

t_gnllst	*ft_lst_by_fd(int fd, t_gnllst **list)
{
	t_gnllst *prev;
	t_gnllst *l;

	if (!*list)
	{
		*list = ft_lstgnlnew(fd);
		return (*list);
	}
	l = *list;
	while (l)
		if (fd == l->fd)
			return (l);
		else
		{
			prev = l;
			l = l->next;
		}
	prev->next = ft_lstgnlnew(fd);
	return (prev->next);
}

void		ft_lst_remove(int fd, t_gnllst **list)
{
	t_gnllst *prev;
	t_gnllst *curr;

	curr = *list;
	if (curr->fd == fd)
	{
		curr = curr->next;
		free(*list);
		*list = curr;
		return ;
	}
	prev = curr;
	curr = curr->next;
	while (curr)
	{
		if (curr->fd == fd)
		{
			prev->next = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
