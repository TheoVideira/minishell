/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaped_characters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:28:29 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 00:35:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	merge_tokens(char *ptr, size_t len, int nb, char **tok)
{
	char	*start;
	char	*new;
	char	*offset;
	size_t	l;

	if ((new = ft_calloc(1, sizeof(char) * (len - nb + 1))) == 0)
		return (ALLOC_ERROR);
	start = ptr;
	offset = new;
	while (len--)
	{
		if (*ptr == '\0')
		{
			l = ptr - start;
			ft_memcpy(offset, start, l);
			offset += l;
			start = ptr + 1;
		}
		ptr++;
	}
	*tok = new;
	return (0);
}

static int	replace_backslash(char *ptr)
{
	int nb;

	nb = 0;
	while (*ptr)
	{
		if (*ptr == '\\')
		{
			*ptr = '\0';
			ptr++;
			nb++;
		}
		ptr++;
	}
	return (nb);
}

static int	replace_backslash_dq(char *ptr)
{
	int nb;

	nb = 0;
	while (*ptr)
	{
		if (*ptr == '\\' && *(ptr + 1)
			&& (*(ptr + 1) == '"' || *(ptr + 1) == '\\'))
		{
			*ptr = '\0';
			ptr++;
			nb++;
		}
		ptr++;
	}
	return (nb);
}

int			replace_escaped(char **token, int indq)
{
	char	*ptr;
	size_t	len;
	int		r;
	int		nb;

	ptr = *token;
	if (!ptr || ft_strchr(ptr, '\\') == 0)
		return (0);
	len = ft_strlen(ptr);
	if (indq)
		nb = replace_backslash_dq(ptr);
	else
		nb = replace_backslash(ptr);
	if ((r = merge_tokens(*token, len + 1, nb, &ptr)))
		return (r);
	free(*token);
	*token = ptr;
	return (0);
}
