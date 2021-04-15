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
		error_message("command not found", all);
		exit(1);
	}
	forks = wait(&forks);
}

char	*defin_dir(t_all *all, char **complete_cmd)
{
	int	a;
	char	**path_bin;
	char	*line;
	char	*tmp;
	t_list	*tmp_env;

	a = -1;
	line = NULL;
	path_bin = NULL;
	tmp_env = env_srh(all, "PATH");
	if (tmp_env)
		path_bin = ft_split(tmp_env->content->value, ':');
	while (path_bin[++a])
	{
		tmp = verify_dir(path_bin[a], all->token->command);
		if (tmp)
		{
			line = ft_strjoin(path_bin[a], tmp);
			free(tmp);
			return (line);
		}
	}
	if (path_bin)
		free_array(&path_bin);
	return (tmp);
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
	line = defin_dir(all, &cmd1);
	if (line)
	{
		open_apk(line, argv, all);
		free(line);
	}
	else
		open_apk(all->token->command, argv, all);

}
