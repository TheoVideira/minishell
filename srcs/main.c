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
	while (str[end] && str[end] != '=')
		end++;
	return (ft_substr(str, start, end));
}

char	*getenvvalue(char *str)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (str[start] && str[start] != '=')
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
			ft_dictclear(dict, 0);
			return (0);
		}
		ft_dictadd(&dict, tmp);
		env++;
	}
	return (dict);
}

char	**dictoenv(t_dict *dict)
{ 
	int len1;
	int len2;
	int i;
	char **env;

	len1 = ft_dictsize(dict);
	if (!(env = ft_calloc(1, (len1 + 1) * sizeof(char*))))
		return (0);
	i = 0;
	while (dict)
	{
		len1 = ft_strlen(dict->key);
		len2 = ft_strlen((char*)dict->value);
		if (!(env[i] = ft_calloc(1, (len1 + 1 + len2 + 1) * sizeof(char))))
		{
			free_char_array(env);
			return (0);	
		}
		ft_memcpy(env[i], dict->key, len1);
		env[i][len1] = '=';
		ft_memcpy(env[i] + len1 + 1, (char*)dict->value, len2);
		dict = dict->next;
		i++;
	}
	return (env);
}

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

int main(int ac, char **av, char **env)
{
	t_minishell mini = {0};
	int			r;
	char		*line;
	t_list		*tokens; 
	(void)ac;
	(void)av;
	(void)env;
	(void) r;

	
	mini.env = envtodict(env);

	while (1)
	{
		write(1, "\e[1;35mOK-BOOMER\e[0m$>", 23);
		r = get_next_line(0, &line);
		
		// if (r == -1)
		// 	if (errno)
		// 		perror(strerror(errno));
		// //Parse
		// job = parse_instruction(line);
		// //Execute
		// execute_instruction(job);
		// free_instruction(job);
		if (r == 0)
		{
			// exit builtin
			free(line);
			break ;
		}

		r = tokenize(line, &tokens);
		if (r == ALLOC_ERROR)
		{
			ft_lstclear(&tokens, free);
			free(line);
			ft_putstr_fd("minishell: allocation error while parsing\n", 2);
			continue;
		}
		printf("\e[1;32m1: TOKENIZER\e[0m\n");
		printf("Listing tokens\n");
		t_list *tok = tokens;
		while (tok)
		{
			printf("|%s|\n",(char*)tok->content);
			tok = tok->next;
		}
		printf("Just tokenized |%s|\n", line);
		free(line); // IMPORTANT
		
		
		
		
		
		printf("\e[1;32m2: PARSER\e[0m\n");
		t_node *root = { 0 };

		r = parse_entry(&tokens, &root);
		if (r == PARSING_ERROR)
		{
			if (!tokens)
				ft_putstr_fd("minishell: syntax error: unexpected end of line\n", 2);	
			else
				ft_perror_msg("minishell", "syntax error near unexpected token", 0, (char*)tokens->content);	
			free_node(root);
			continue ;
		}
		if (r == ALLOC_ERROR)
		{
			ft_lstclear(&tokens, free);
			ft_putstr_fd("minishell: allocation error while parsing\n", 2);
			continue;
		}
		if (r == FATAL_ERROR)
		{
			ft_perror("minishell", "a weird error has occured", 0);
			ft_lstclear(&tokens, free);
			free_node(root);
			continue;
		}

		
		printf("Just parsed\n");
		print_tree(root);
		printf("-------------------------------\n");
		




		// tok = tokens;
		// while (tok)
		// {
		// 	printf("THIS SHOULD NOT APPEAR\n");
		// 	printf("\"%s\"\n",(char*)tok->content);
		// 	tok = tok->next;
		// }
		// printf("\e[1;32m3: INTERPRETER\e[0m\n");
		// printf("-------------OUTPUT------------\n");
		
		// run_tree(root->obj, &mini);
		// free_node(root);
		// printf("--------------END--------------\n");
	}
	ft_dictclear(mini.env, free);
	//Think about freeing if signal caught
	return (0);
}
