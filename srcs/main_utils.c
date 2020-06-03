/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 21:36:56 by user42            #+#    #+#             */
/*   Updated: 2020/06/03 03:38:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			lexer(char *line, t_list **tokens)
{
	int	r;

	r = tokenize(line, tokens);
	if (r == ALLOC_ERROR)
	{
		ft_lstclear(tokens, free);
		alloc_error();
		return (r);
	}
	if (r == QUOTE_NOT_CLOSED)
	{
		ft_lstclear(tokens, free);
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (r);
	}
	return (0);
}

static void		parsing_error(t_list **tokens, t_entry **entry)
{
	if (!*tokens)
		ft_putstr_fd(
				"minishell: syntax error: unexpected end of line\n", 2);
	else
		ft_perror_msg("minishell", "syntax error near unexpected token",
											0, (char*)(*tokens)->content);
	ft_lstclear(tokens, free);
	free_entry(*entry);
	g_mini.lastcall = 2;
}

int				parser(t_list **tokens, t_entry **entry)
{
	int r;

	r = parse_entry(tokens, entry);
	if (r == PARSING_ERROR)
		parsing_error(tokens, entry);
	else if (r == ALLOC_ERROR)
	{
		ft_lstclear(tokens, free);
		alloc_error();
	}
	else if (r == FATAL_ERROR)
	{
		fatal_error();
		ft_lstclear(tokens, free);
		free_entry(*entry);
	}
	return (r);
}

void		interpreter(t_entry *entry)
{
	run_entry(entry);
}

void		run_dat_shit(char *line)
{
	t_list		*tokens;
	t_entry		*entry;

	if (ft_strlen(line) == 0 || is_only_space(line))
		return ;
	if (lexer(line, &tokens))
		return ;
	if (parser(&tokens, &entry))
		return ;
	interpreter(entry);
	free_entry(entry);
}
