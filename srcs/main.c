/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:50:20 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/04 18:09:53 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	int				r;
	(void) r;
	// t_instruction	*job;

	char	*line;
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
		printf("Listing tokens\n");
		while (tokens)
		{
			printf("\"%s\"\n",(char*) tokens->content);
			tokens = tokens->next;
		}
		printf("Just tokenized \"%s\"\n", line);
		free(line);
		t_instruction *ins;
		if (parse_instruction(tok, &ins) == -1)
			printf("\e[1;31mSYNTAX ERROR\e[0m\n");
		printf("Just parsed\n");
		print_tree(ins->tree);

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
