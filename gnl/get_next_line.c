/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 10:58:05 by mclaudel          #+#    #+#             */
/*   Updated: 2020/06/05 21:39:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*substr_gnl(char const *s, unsigned int start, int len)
{
	char	*dest;
	int		i;

	if (len < 0)
		len = 0;
	if (!(dest = (malloc(len + 1))))
		return (0);
	dest[len] = 0;
	i = 0;
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int			managecharsleft(t_gnllst *l, t_line *s_line)
{
	char	*tmp;
	int		e;

	if (l->charsleft == 0)
		return (0);
	if ((e = endofline(l->charsleft, l->size)) != -1)
	{
		if (!(*(s_line->line) = substr_gnl(l->charsleft, 0, e)))
			return (-1);
		tmp = l->charsleft;
		if (l->size == e + 1)
			l->charsleft = 0;
		else if (!(l->charsleft = substr_gnl(l->charsleft, e + 1, l->size - e)))
			return (-1);
		free(tmp);
		l->size -= e + 1;
		return (1);
	}
	else
	{
		*(s_line->line) = l->charsleft;
		l->charsleft = 0;
		s_line->size = l->size;
		return (l->size = 0);
	}
}

int			allocandconcat(t_line *s_line, char *buff, int tocpy)
{
	char *tmp;

	tmp = *(s_line->line);
	if (!(*(s_line->line) =
		ft_memjoin(*(s_line->line), s_line->size, buff, tocpy)))
		return (-1);
	s_line->size += tocpy;
	free(tmp);
	return (0);
}

int			readloop(int fd, char *buff, t_line *s_line, t_gnllst *current)
{
	int rd;
	int eol;
	int i;

	ft_bzero(buff, BUFFER_SIZE);
	while ((rd = read(fd, buff, BUFFER_SIZE)) > 0 &&
		(eol = endofline(buff, BUFFER_SIZE)) == -1)
	{
		if (allocandconcat(s_line, buff, rd))
			return (-1);
		ft_bzero(buff, BUFFER_SIZE);
	}
	if (rd == -1)
		return (-1);
	if (rd == 0)
		return (0);
	if (allocandconcat(s_line, buff, eol))
		return (-1);
	i = rd - eol - 1;
	if (eol + 1 == rd)
		current->charsleft = 0;
	else if (i > 0 && !(current->charsleft = substr_gnl(buff, eol + 1, i)))
		return (-1);
	current->size = i < 0 ? 0 : i;
	return (i < 0 ? 0 : 1);
}

int			get_next_line(int fd, char **line)
{
	static t_gnllst	*list;
	t_gnllst		*current;
	t_line			s_line;
	char			*buff;
	int				i;

	if (BUFFER_SIZE < 0 ||
		!line || fd < 0 || !(current = ft_lst_by_fd(fd, &list)))
		return (-1);
	*line = 0;
	s_line = (t_line) {.size = 0, .line = line};
	if ((i = managecharsleft(current, &s_line)) == 1)
		return (1);
	if (i == -1 || !(buff = malloc(sizeof(char) * BUFFER_SIZE)))
		return (-1);
	if ((i = readloop(fd, buff, &s_line, current)) == 0 && !*line)
	{
		if (!(*line = malloc(1)))
			return (-1);
		*line[0] = '\0';
	}
	if (i == 0)
		ft_lst_remove(fd, &list);
	free(buff);
	return (i);
}
