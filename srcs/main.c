/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:50:20 by mclaudel          #+#    #+#             */
/*   Updated: 2020/03/12 17:07:57 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


//DEBUG
void	printdict(t_dict *dict)
{
	printf("\e[31;1m ENV \e[0m\n");
	while(dict)
	{
		printf("%s=%s\n", dict->key, (char *)dict->value);
		dict = dict->next;
	}
}


static int lexer(char *line, t_list	**tokens)
{
	int r;

	r = tokenize(line, tokens);
	if (r == ALLOC_ERROR)
	{
		ft_lstclear(tokens, free);
		free(line);
		ft_putstr_fd("minishell: allocation error while parsing\n", 2);
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

		r = parse_entry(tokens, entry);
		if (r == PARSING_ERROR)
		{
			if (!*tokens)
				ft_putstr_fd("minishell: syntax error: unexpected end of line\n", 2);	
			else
				ft_perror_msg("minishell", "syntax error near unexpected token", 0, (char*)(*tokens)->content);	
			free_entry(*entry);
	
		}
		else if (r == ALLOC_ERROR)
		{
			ft_lstclear(tokens, free);
			ft_putstr_fd("minishell: allocation error while parsing\n", 2);
		}
		else if (r == FATAL_ERROR)
		{
			ft_perror("minishell", "a weird error has occured", 0);
			ft_lstclear(tokens, free);
			free_entry(*entry);
		}
		else
		{
			/* code */
		printf("\e[1;32m2: PARSER\e[0m\n");

		
		printf("Just parsed\n");
		t_list *tree;
		tree = (*entry)->instructions;
		while (tree)
		{
			print_tree((t_node*)tree->content);
			tree = tree->next;
			printf("-------------------------------\n");
		}
		}
		return (r);
}

static int interpreter(t_entry *entry, t_minishell *mini)
{
		int r;
		printf("\e[1;32m3: INTERPRETER\e[0m\n");
		printf("-------------OUTPUT------------\n");
		r = run_entry(entry, mini);
		printf("--------------END--------------\n");
		return (r);
}

static void run_dat_shit(char *line, t_minishell *mini)
{
	t_list		*tokens;
	t_entry		*entry;

	if (lexer(line, &tokens))
		return ;
	free(line);
	if (parser(&tokens, &entry))
		return ;
	if (interpreter(entry, mini))
		return ;
	free_entry(entry);
}

int main(int ac, char **av, char **env)
{
	t_minishell mini = {0};
	int			r;
	char		*line;
	
	(void) ac;
	(void) av;
	mini.env = envtodict(env);
	while (1)
	{
		write(1, "\e[1;35mOK-BOOMER\e[0m$>", 23);
		r = get_next_line(0, &line);
		if (r == 0)
		{
			free(line);
			break ;
		}
		run_dat_shit(line, &mini);				
	}
	ft_dictclear(mini.env, free);
	return (0);
}
