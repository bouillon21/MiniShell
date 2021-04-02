#include "minishell.h"

char	*verify_dir(char *path, char *cmd)
{
	DIR	*direct;
	struct dirent	*dir_file;

	direct = opendir(path);
	if (!direct)
	{
		closedir(direct);
		return (NULL);
	}
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
	int	a;
	pid_t	forks;
	char	**env_copy;
	t_list	*env;

	env = all->env;
	forks = fork();
	if (forks == 0)
	{
		env_copy = env_join(env);
		execve(path, argv, env_copy);
	}
	wait(&a);
}

char	**defin_dir(t_all *all, char **cmd)
{
	char	**path_bin;
	char	*line;

	if (ft_strncmp(*cmd, "./", 2) == 0)
	{
		line = env_srh(all, "PWD=")->content;
		path_bin = ft_split(&line[4], ':');
		*cmd = ft_substr(*cmd, 2,ft_strlen(*cmd) - 2);
	}
	else
	{
		line = env_srh(all, "PATH=")->content;
		path_bin = ft_split(&line[5], ':');
	}
	return (path_bin);
}

void	exec(char **argv, t_all *all, char *cmd)
{
	int	a;
	char	*line;
	char	**path_bin;
	char	*tmp;
	
	a = 0;
	path_bin = defin_dir(all, &cmd);
	while (path_bin[a])
	{
		tmp = verify_dir(path_bin[a], cmd);
		if (tmp)
		{
			line = ft_strjoin(path_bin[a], tmp);
			open_apk(line, argv, all);
			free(tmp);
			free(line);
		}
		a++;
	}
	free(cmd);
	free_array(&path_bin);
}