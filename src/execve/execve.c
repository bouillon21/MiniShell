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
	int	tmp;

	env = all->env;
	forks = fork();
	if (forks == 0)
	{
		env_copy = env_join(env);
		terminal_off(all);
		// terminal(all);
		execve(path, argv, env_copy);
	}
	wait(&forks);
}

char	**defin_dir(t_all *all, char *cmd)
{

	char	**path_bin;
	char	*line;

	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		line = ft_strdup(env_srh(all, "PWD")->content->value);
		path_bin = ft_split(line, ':');
		free(line);
		cmd = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
	}
	else
		path_bin = ft_split(env_srh(all, "PATH")->content->value, ':');
	return (path_bin);
}

void	exec(t_all *all)
{
	int	a;
	char	*line;
	char	**path_bin;
	char	*tmp;
// cделать защиту от null
// переделать в all
	// printf_env(all);
	// printf("\n\n\n\n\n");
	// env_add(all,"PWD", env_srh(all, "PWD")->content->value);
	// printf("\n\n\n\n\n");
	// printf_env(all);

	
	a = -1;
	path_bin = defin_dir(all, all->token->command);
	// printf("2nd - %s\n", env_srh(all, "PWD")->content->value);
	while (path_bin[++a])
	{
		tmp = verify_dir(path_bin[a], all->token->command);
		if (tmp)
		{
			line = ft_strjoin(path_bin[a], tmp);
			open_apk(line, all->token->args, all);
			free(tmp);
			free(line);
			break;
		}
		if (!path_bin[a + 1])
			error_message("command not found", all);
	}
	free_array(&path_bin);
}