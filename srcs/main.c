/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:50:20 by mclaudel          #+#    #+#             */
/*   Updated: 2020/06/02 02:23:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell mini = {0};

static int lexer(char *line, t_list	**tokens)
{
	int r;

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
		ft_putstr_fd("minishell: unclosed quote you scumbag\n", 2);
		return (r);
	}
	printf("\e[1;32m1: TOKENIZER\e[0m\n");
	printf("Listing tokens\n");
	t_list *tok = *tokens;
	while (tok)
	{
		printf("|%s|\n",(char*)tok->content);
		tok = tok->next;
	}
	printf("Just tokenized |%s|\n", line);
	return (0);
}

static int parser(t_list **tokens, t_entry **entry)
{
	int r;

	printf("\e[1;32m2: PARSER\e[0m\n");
	r = parse_entry(tokens, entry);
	if (r == PARSING_ERROR)
	{
		if (!*tokens)
			ft_putstr_fd("minishell: syntax error: unexpected end of line\n", 2);	
		else
			ft_perror_msg("minishell", "syntax error near unexpected token", 0, (char*)(*tokens)->content);	
		ft_lstclear(tokens, free);
		free_entry(*entry);
		mini.lastcall = 2;
	}
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
	else
	{
		printf("Just parsed\n");
		t_list *tree;
		tree = (*entry)->instructions;
		while (tree)
		{
			print_tree((t_node*)tree->content);
			tree = tree->next;
		}
	}
	printf("-------------------------------\n");
	return (r);
}

static void interpreter(t_entry *entry)
{
	printf("\e[1;32m3: INTERPRETER\e[0m\n");
	printf("-------------OUTPUT------------\n");
	run_entry(entry);
	printf("--------------END--------------\n");
}

static void run_dat_shit(char *line)
{
	t_list		*tokens;
	t_entry		*entry;

	if (ft_strlen(line) == 0)
		return ;
	if (lexer(line, &tokens))
		return ;
	if (parser(&tokens, &entry))
		return ;
	interpreter(entry);
	free_entry(entry);
}

int main(int ac, char **av, char **env)
{
	int			r;
	char		*line;
	
	(void) ac;
	(void) av;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	mini.env = envtodict(env);
	mini.isparent = 1;
	r = 1;
	line = 0;
	while (1)
	{
		if (!(r == 0 && *line))
			write(1, "\e[1;35mOK-BOOMER\e[0m$>", 23);
		r = get_next_line(0, &line);
		if (r == 0 && *line)
			continue ;
		if (r == 0)
		{
			ft_dictclear(mini.env, free);
			free(line);
			builtin_exit(1, 0);
		}
		run_dat_shit(line);
		free(line);
	}
	ft_dictclear(mini.env, free);
	return (0);
}
