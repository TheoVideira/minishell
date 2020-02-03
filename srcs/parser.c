/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 11:23:51 by mclaudel          #+#    #+#             */
/*   Updated: 2020/02/03 17:22:30 by mclaudel         ###   ########.fr       */
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

int		tokencount(char *str)
{
	int		inquotes;
	int		count;

	count = 0;
	while (*str)
	{
		inquotes = 0;
		while (ft_isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		if ((*str == '\'' || *str == '\"') && (inquotes = *str))
			str++;
		while (*str && (inquotes || !ft_isspace(*str)))
		{
			if (*str == inquotes && str++)
				break ;
			if (!inquotes && (*str == '|' || *str == ';'))
			{
				str++;
				count++;
				break ;
			}
			str++;
		}
		count++;
	}
	return (count);
}


char *double_quotes(char *str)
{
	int		size;
	char	token;

	size == 0;
	while (*str && *str != '"')
		size++;
	token = ft_calloc(1, sizeof(char) * (size + 1));
	ft_strlcpy(token, str - size, size);
	//replace stuff
}

char *single_quotes(char *str)
{
	

}

char *no_quotes(char *str)
{
	//copy chars
	//replace stuff
}



char	*get_next_token(char *str)
{
	char *token;
	char *subtoken;
	char *tmp;
	int nb;

	while (ft_isspace(*str))
		str++;
	nb = 0;
	while (*str && !ft_isspace(*str))
	{
		//CHECK FO PIPE OR OTHER SEPARATORS
		// if (*str == '|')

		if (*str == '"')
			subtoken = double_quotes(str);
		else if (*str == '\'')
			subtoken = single_quotes(str);
		else
			subtoken = no_quotes(str);
		tmp = token;
		token = ft_strjoin(token, subtoken);
		str += ft_strlen(subtoken) + 1;
		free(tmp);
		free(subtoken);
		nb++;
	}
	// if (nb == 1)
}

char	**tokenize(char *str)
{
	char	**tokens;
	int		i;

	tokens = ft_calloc(1, sizeof(char*) * (tokencount(str) + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	while (*str)
	{
		tokens[i] = get_next_token(str);
		str += ft_strlen(tokens[i]);
		i++;
	}
	return (tokens);
}
