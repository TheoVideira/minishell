/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:34:42 by user42            #+#    #+#             */
/*   Updated: 2020/06/14 18:55:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	compute_full_path(char *dirname, char *bin, char **fullpath)
{
	size_t			lendir;
	size_t			lenbin;
	unsigned int	slash;
	char			*fullname;

	lendir = ft_strlen(dirname);
	lenbin = ft_strlen(bin);
	slash = dirname[lendir - 1] == '/';
	if (!(fullname = ft_calloc(1,
			sizeof(char) * (lendir + lenbin + !slash + 1))))
		return (ALLOC_ERROR);
	ft_strlcpy(fullname, dirname, lendir + 1);
	if (!slash)
		fullname[lendir] = '/';
	ft_strlcpy(fullname + lendir + !slash, bin, lenbin + 1);
	*fullpath = fullname;
	return (0);
}

int			search_dir(char *dirname, char *label, char **fullpath)
{
	DIR				*dir;
	struct dirent	*de;
	int				r;

	if ((dir = opendir(dirname)) == 0)
	{
		return (FATAL_ERROR);
	}
	r = 0;
	while ((de = readdir(dir)))
	{
		// printf("ENTRY |%s|\n", de->d_name);
		if (ft_strcmp(label, de->d_name) == 0)
		{
			r = compute_full_path(dirname, de->d_name, fullpath);
			if (r == 0)
				r = 1;
			break ;
		}
	}
	free(dir);
	return (r);
}
