#include <minishell.h>

int		ask_for_more(t_list **token)
{
	int r;
	char *line;
	int len;

	len = 0;
	while (len == 0)
	{		
		write(1, ">", 1);
		r = get_next_line(0, &line);
		if (r == -1)
			return (-1);
		len = ft_strlen(line);
	}
	tokenize(line, token);
	return(0);
}