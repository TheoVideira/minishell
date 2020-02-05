/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 11:23:51 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/04 18:26:52 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// t_instruction	*parse_instruction(char *str)
// {
	
// }


// t_pipeline		*parse_pipeline(char *str)
// {

// }

// t_cmd			*parse_cmd(char *str)
// {

	
// 	while (str)

// }

int		is_separator(char *str)
{
	if (*str == '&' && *(str + 1) == '&')
		return (2);
	if (*str == '|' && *(str + 1) == '|')
		return (2);
	if (*str == '(')
		return (1);
	if (*str == ')')
		return (1);
	if (*str == '|')
		return (1);
	if (*str == ';')
		return (1);
	return (0);
}

int		double_quotes(char *str, char **token)
{
	int		size;

	size = 0;
	while (*str && *str != '"')
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1));
	ft_memcpy(*token, str - size, size);
	//replace stuff
	return (size);
}

int		single_quotes(char *str, char **token)
{
	int		size;

	size = 0;
	while (*str && *str != '\'')
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1));
	ft_memcpy(*token, str - size, size);
	return (size);
}

int		no_quotes(char *str, char **token)
{
	int		size;

	size = 0;
	while (*str && !ft_isspace(*str) && *str != '"' && *str != '\'' && !is_separator(str))
	{
		size++;
		str++;
	}
	*token = ft_calloc(1, sizeof(char) * (size + 1));
	ft_memcpy(*token, str - size, size);
	//replace stuff
	return (size);
}


char		*handle_separators(char *str)
{
	if (*str == '&' && *(str + 1) == '&')
		return (ft_strdup("&&"));
	if (*str == '|' && *(str + 1) == '|')
		return (ft_strdup("||"));
	if (*str == '(')
		return (ft_strdup("("));
	if (*str == ')')
		return (ft_strdup(")"));
	if (*str == '|')
		return (ft_strdup("|"));
	if (*str == ';')
		return (ft_strdup(";"));
	return (0);
}

int			get_next_token(char *str, char **tofill)
{
	char *token;
	char *subtoken;
	char *tmp;
	char *start;

	token = ft_calloc(1, 1); // check if null or redo strjoin to handle null
	start = str;
	while (ft_isspace(*str))
		str++;
	while (*str && !ft_isspace(*str))
	{
		if ((subtoken = handle_separators(str)))
			str += ft_strlen(subtoken);
		else if (*str == '"')
			str += double_quotes(str + 1, &subtoken) + 2;
		else if (*str == '\'')
			str += single_quotes(str + 1, &subtoken) + 2;
		else
			str += no_quotes(str, &subtoken);
		tmp = token;
		token = ft_strjoin(token, subtoken);
		free(tmp);
		free(subtoken);
		if (is_separator(str) || is_separator(token))
			break;
	}
	*tofill = token;
	return ((unsigned int)(str - start));
}

t_list	*tokenize(char *str)
{
	t_list	*tokens;
	char	*token;
	int		tmp;

	tokens = 0;
	while ((tmp = get_next_token(str, &token)))
	{
		ft_lstadd_back(&tokens, ft_lstnew(token)); // check for new null
		str += tmp;
	}
	return (tokens);
}
