#include <minishell.h>


static char *search_dir(char *dirname, char *label)
{
	DIR *dir;
	struct dirent *de;
	char **tab;
	int i;

	if (!(dir = opendir(dirname)))
	{
		//could not open directory
		return (0);
	}
	while ((de = readdir(dir)))
	{
		i = 0;
		tab = ft_split(de->d_name, '/');
		while (tab[i])
		{
			if (ft_strcmp(label, tab[i]) == 0)
			{
				free_char_array(tab);
				return (de->d_name);
			}
			i++;
		}
		free_char_array(tab);
	}
	free(dir);
	return (0);
}

static char *compute_full_path(char *dirname, char *bin)
{
	size_t lendir;
	size_t lenbin;
	unsigned int slash;
	char *fullname;

	lendir = ft_strlen(dirname);
	lenbin = +ft_strlen(bin);
	slash = dirname[lendir - 1] == '/';
	if (!(fullname = ft_calloc(1, sizeof(char) * (lendir + lenbin + !slash + 1))))
		return (0);
	ft_strlcpy(fullname, dirname, lendir + 1);
	if (!slash)
		fullname[lendir] = '/';
	ft_strlcpy(fullname + lendir + !slash, bin, lenbin + 1);
	return (fullname);
}

static char *find_name(char *label, t_minishell *mini)
{
	char *path;
	char **entries;
	char *name;
	char *r;
	int i;

	name = 0;
	path = (char *)ft_dictget(mini->env, "PATH");
	if (!(entries = ft_split(path, ':')))
	{
		// panic
		return (0);
	}
	i = 0;
	while (entries[i])
	{
		if ((name = search_dir(entries[i], label)))
		{
			if (!(r = compute_full_path(entries[i], name)))
			{
				// panic
				return (0);
			}
			free_char_array(entries);
			return (r);
		}
		i++;
	}
	free_char_array(entries);
	return (0);
}

static void	launch_file(t_cmd *cmd, t_minishell *mini)
{
	struct stat tmp;

	if (stat(cmd->label, &tmp) == -1)
		ft_perror("minishell", "cannot access", cmd->label); // check the right error message
	
	if(tmp.st_mode & S_IEXEC && !S_ISDIR(tmp.st_mode)) 
		execve(cmd->label, cmd->args, mini->envtmp);
	else
	{
		ft_perror(0, "command not found", cmd->label);
		exit(1);	
	}
}

int run_command(t_cmd *cmd, t_minishell *mini)
{
	char *path;	
	int r;
	int fd;

	if ((fd = handle_redirs(cmd->redir)) == -1)
	{
		exit(errno);
	}
	if ((r = execute_builtin(cmd, mini)) > -1)
	{
		// mini->lastcall = r;
		// free all shit
		close(fd);
		exit(r);
	}
	//if file


	if ((ft_strncmp("./", cmd->label, 2) == 0 || ft_strchr(cmd->label, '/')))
		launch_file(cmd, mini);
	

	//if not
	path = find_name(cmd->label, mini);
	execve(path, cmd->args, mini->envtmp); // need to add env trad
	ft_perror("minishell", "command not found", cmd->label);
	printf("%d\n", errno);
	mini->lastcall = 127;
	exit(1);
	return (0);
}