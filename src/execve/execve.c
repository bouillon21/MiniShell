#include "minishell.h"

char	**env_join(t_list *env)
{
	int	i;
	char	**env_copy;
	
	i = 0;
	env_copy = malloc(sizeof(char *) * ft_lstsize(env));
	if (!env_copy)
		return (NULL);
	while (env->next)
	{
		env_copy[i] = ft_strdup(env->content);
		env = env->next;
		i++;
	}
	env_copy[i] = ft_strdup(env->content);
	return (env_copy);
}

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
	return(NULL);
}

void	free_array(char ***mas)
{
	int	i;

	i = 0;
	while ((*mas)[i])
	{
		free((*mas)[i]);
		i++;
	}
	free(*mas);
}

void	open_apk(char *path, char **argv, t_list *env)
{
	int	a;
	pid_t	forks;
	char	**path_bin;
	char	**env_copy;

	// printf("%s\n", argv[1]);
	forks = fork();
	if (forks == 0)
	{
		env_copy = env_join(env);
		execve(path, argv, env_copy);
	}
	wait(&a);
}

void	exec(char **argv, t_list *env, char *cmd)
{
	pid_t forks;
	int	a;
	char	*line;
	char	**path_bin;
	char	*tmp;
	char	*ad[3];

	ad[0] = ft_strdup("minishell");
	ad[1] = ft_strdup("uipiouiuy");
	// ad[2] = NULL;
	
	a = 0;

	// while (argv[a])
	// {
	// 	printf("%s\n", argv[a]);
	// 	a++;
	// }
	path_bin = ft_split(env_srh(&env, "PATH="), ':');
	while (path_bin[a])
	{
		line = verify_dir(path_bin[a], cmd);
		if (line)
		{
			printf("%s\n", line);
			open_apk("/bin/echo", ad, env);
		}
		free(line);
		a++;
	}
	free_array(&path_bin);
	// if (forks == 0)
	// {
	// 	execve("/bin/./ls", argv, env_copy);
	// }
	// wait(&a);
	// printf("ya goul\n");
}