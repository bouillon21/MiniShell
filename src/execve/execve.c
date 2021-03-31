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

void	open_apk(char *path, char **argv, t_list *env)
{
	int	a;
	pid_t	forks;
	char	**env_copy;

	forks = fork();
	if (forks == 0)
	{
		env_copy = env_join(env);
		execve(path, argv, env_copy);
	}
	wait(&a);
}

char	**defin_dir(t_list *env, char **cmd)
{
	char	**path_bin;

	if (ft_strncmp(*cmd, "./", 2) == 0)
	{
		path_bin = ft_split(env_srh_edit(&env, "PWD=", NULL), ':');
		*cmd = ft_substr(*cmd, 2,ft_strlen(*cmd) - 2);
	}
	else
		path_bin = ft_split(env_srh_edit(&env, "PATH=", NULL), ':');
	return (path_bin);
}

void	exec(char **argv, t_list *env, char *cmd)
{
	int	a;
	char	*line;
	char	**path_bin;
	char	*tmp;
	
	a = 0;
	path_bin = defin_dir(env, &cmd);
	while (path_bin[a])
	{
		tmp = verify_dir(path_bin[a], cmd);
		if (tmp)
		{
			line = ft_strjoin(path_bin[a], tmp);
			open_apk(line, argv, env);
			free(tmp);
			free(line);
		}
		a++;
	}
	free(cmd);
	free_array(&path_bin);
}