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

char	**defin_dir(t_all *all, char *cmd)
{
	char	**path_bin;
	char	*line;
	char	*tmp;

	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		path_bin = ft_split(env_srh(all, "PWD")->content->value, ':');
		free (all->token->command);
		all->token->command = ft_strdup(ft_strchr(cmd, '/') + 1);
	}
	else
		path_bin = ft_split(env_srh(all, "PATH")->content->value, ':');
	return (path_bin);
}

void	exec(char **argv, t_all *all, char *cmd)
{
	int	a;
	char	*line;
	char	**path_bin;
	char	*tmp;
// cделать защиту от null
// переделать в all
	a = -1;
	path_bin = defin_dir(all, cmd);
	while (path_bin[++a])
	{
		tmp = verify_dir(path_bin[a], all->token->command);
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