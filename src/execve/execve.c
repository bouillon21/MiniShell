#include "minishell.h"

char	*verify_dir(char *path, char *cmd)
{
	DIR	*direct;
	struct dirent	*dir_file;

	direct = opendir(path);
	if (!direct)
		return (NULL);
	dir_file = readdir(direct);
	while (dir_file)
	{
		if (ft_strncmp(dir_file->d_name, cmd, ft_strlen(cmd) + 4) == 0)
		{
			closedir(direct);
			return (ft_strjoin("/./",dir_file->d_name));
		}
		dir_file = readdir(direct);
	}
	closedir(direct);
	return(NULL);
}

void	open_apk(char *path, char **argv, t_all *all)
{
	pid_t	forks;
	char	**env_copy;
	t_list	*env;

	env = all->env;
	forks = fork();
	if (forks == 0)
	{
		env_copy = env_join(env);
		terminal_off(all);
		execve(path, argv, env_copy);
	}
	forks = wait(&forks);
}

char	**defin_dir(t_all *all, char **complete_cmd)
{
	char	**path_bin;
	char	*line;
	char	tmp[1024];
	t_list	*tmp_env;

	path_bin = NULL;
	if (all->token->command[0] == '.')
	{
		path_bin = ft_calloc(sizeof(char *), 2);
		path_bin[0] = ft_strdup(getcwd(tmp, 1024));
		*complete_cmd = ft_strdup(ft_strchr(all->token->command, '/') + 1);
	}
	else if (all->token->command[0] == '/')
	{
		path_bin = ft_calloc(sizeof(char *), 2);
		path_bin[0] = ft_substr(all->token->command, 0,
			ft_strlen(all->token->command)
				- ft_strlen(ft_strrchr(all->token->command , '/')));
		*complete_cmd = ft_strdup(ft_strrchr(all->token->command, '/') + 1);
	}
	else
	{
		*complete_cmd = ft_strdup(all->token->command);
		tmp_env = env_srh(all, "PATH");
		if (tmp_env)
			path_bin = ft_split(tmp_env->content->value, ':');
		else
		{
			path_bin = ft_calloc(sizeof(char *), 2);
			path_bin[0] = ft_strdup(getcwd(tmp, 1024));
		}
	}
	return (path_bin);
}

void	exec(char **argv, t_all *all, char *cmd)
{
	int		a;
	char	*line;
	char	**path_bin;
	char	*tmp;
	char	*cmd1;
// cделать защиту от null ?? Команды может и не быть в случае редиректов.
// переделать в all
	a = -1;
	path_bin = defin_dir(all, &cmd1);
	if (path_bin)
	{
		while (path_bin[++a])
		{
			tmp = verify_dir(path_bin[a], cmd1);
			if (tmp)
			{
				line = ft_strjoin(path_bin[a], tmp);
				open_apk(line, argv, all);
				free(tmp);
				free(line);
				break;
			}
			if (!path_bin[a + 1])
				error_message("command not found", all);
		}
		free_array(&path_bin);
	}
	free(cmd1);
}
