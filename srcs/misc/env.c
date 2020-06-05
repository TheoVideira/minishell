/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:50:37 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 02:21:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*getenvkey(char *str)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (str[end] && str[end] != '=')
		end++;
	return (ft_substr(str, start, end));
}

char		*getenvvalue(char *str)
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

t_dict		*envtodict(char **env)
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

static int	format_entry(t_dict *dict, char **env, int i)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(dict->key);
	len2 = ft_strlen((char*)dict->value);
	if (!(env[i] = ft_calloc(1, (len1 + 1 + len2 + 1) * sizeof(char))))
	{
		free_char_array(env);
		return (ALLOC_ERROR);
	}
	ft_memcpy(env[i], dict->key, len1);
	env[i][len1] = '=';
	ft_memcpy(env[i] + len1 + 1, (char*)dict->value, len2);
	return (0);
}

int			dictoenv(t_dict *dict)
{
	char	**env;
	int		len;
	int		i;
	int		r;

	len = ft_dictsize(dict);
	if (!(env = ft_calloc(1, (len + 1) * sizeof(char*))))
		return (ALLOC_ERROR);
	i = 0;
	while (dict)
	{
		if (dict->value == 0)
		{
			dict = dict->next;
			continue ;
		}
		if ((r = format_entry(dict, env, i)))
			return (ALLOC_ERROR);
		dict = dict->next;
		i++;
	}
	g_mini.envtmp = env;
	return (0);
}
