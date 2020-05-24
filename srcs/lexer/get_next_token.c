#include <minishell.h>

static int			loop_until(char *str, char end)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == end && str[i - 1] != '\\')
			return (i);
		i++;
	}
	return (i);
}

static int	read_token(char **str)
{
	int		tmp;

	while (**str && !ft_isspace(**str))
	{
		if ((tmp = is_separator(*str)))
		{
			*str += tmp;
			break;
		}	
		else if (**str == '"')
			*str += 1 + loop_until(*str + 1, '"') + 1; // check error
		else if (**str == '\'')
			*str += 1 + loop_until(*str + 1, '\'') + 1; // check error
		else
			(*str)++;
		if (is_separator(*str))
			break ;
		//check uneven quotes
	}
	return (0);
}

int			get_next_token(char *str, char **tofill)
{
	char	*token;
	char	*start;
	char	*tokenstart;
	int		r;

	start = str;
	while (ft_isspace(*str))
		str++;
	tokenstart = str;
	if ((r = read_token(&str)))
		return (r);
	if (str - tokenstart == 0)
	{
		token = 0;
		return (0);
	}
	if (!(token = ft_calloc(1, sizeof(char) * (str - tokenstart + 1)))) // check error
		return (ALLOC_ERROR);
	ft_memcpy(token, tokenstart, str - tokenstart);
	*tofill = token;
	return ((unsigned int)(tokenstart - start + ft_strlen(token)));
}
