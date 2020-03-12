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

char	*getenvkey(char *str)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (str[end] != '=')
		end++;
	return (ft_substr(str, start, end));
}

char	*getenvvalue(char *str)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (str[start] != '=')
		start++;
	start++;
	end = ft_strlen(str) - start;
	return (ft_substr(str, start, end));
}

t_dict	*envtodict(char **env)
{
	t_dict	*dict;
	t_dict	*tmp;
	char	*key;
	char	*value;

	dict = 0;
	if (!env)
		return (0);
	while (*env)
	{
		if (!(key = getenvkey(*env)))
			return (0);
		value = getenvvalue(*env);
		if (!value || !(tmp = ft_dictnew(key, value)))
		{
			free(value);
			ft_dictclear(dict);
			return (0);
		}
		ft_dictadd(&dict, tmp);
		env++;
	}
	return (dict);
}

//DEBUG
void	printdict(t_dict *dict)
{
	printf("\e[31;1m ENV \e[0m\n");
	while(dict)
	{
		printf("%s=%s\n", dict->key, dict->value);
		dict = dict->next;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	int				r;
	(void) r;

	char	*line;

	t_dict *envdict = envtodict(env);
	printdict(envdict);
	while (1)
	{
		write(1, "$>", 3);
		r = get_next_line(0, &line);
		// if (r == -1)
		// 	if (errno)
		// 		perror(strerror(errno));
		// //Parse
		// job = parse_instruction(line);
		// //Execute
		// execute_instruction(job);
		// free_instruction(job);
		// if (r == 0)
		// {
		// 	free(line);
		// 	break ;
		// }
		t_list *tokens = tokenize(line);
		t_list *tok = tokens;
		printf("\e[1;32m1: TOKENIZER\e[0m\n");
		printf("Listing tokens\n");
		while (tokens)
		{
			printf("\"%s\"\n",(char*)tokens->content);
			tokens = tokens->next;
		}
		printf("Just tokenized |%s|\n", line);
		free(line);
		t_entry *ins;
		printf("\e[1;32m2: PARSER\e[0m\n");
		if (parse_entry(&tok, &ins) == -1)
			printf("\e[1;31mSYNTAX ERROR\e[0m\n");
		printf("Just parsed\n");
		while (ins->instructions)
		{
			print_tree((t_node*)ins->instructions->content);
			ins->instructions = ins->instructions->next;
			if (ins->instructions)
				printf("-------------------------------\n");
		}

		// t_node *tree;
		// tree = create_node(OR, 0);
		// tree->left = create_node(AND, 0);
		// tree->right = create_node(PIPELINE, 0);
		// tree->left->left = create_node(PIPELINE, 0);
		// tree->left->right = create_node(OR, 0);
		// tree->left->right->left = create_node(PIPELINE, 0);
		// tree->left->right->right = create_node(PIPELINE, 0);
		// print_tree(tree);
		
		
		// free_tokenarray(tokens);
	}
	//Think about freeing if signal caught
	return (0);
}
