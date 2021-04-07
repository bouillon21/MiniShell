#include "minishell.h"

void	save_old_pwd(t_all *all)
{
	char	*line;
	char	*buf;
	
	buf = malloc(1024);
	getcwd(buf, 1024);
	env_add(all, "OLDPWD=", buf);
	free(buf);
}

int	move_path(t_all *all, char *path)
{
	char	buf[1024];

	save_old_pwd(all);
	if (chdir(path) == -1)
	{
		error_message("No such file or directory", all);
		return(-1);
	}
	getcwd(buf, 1024);
	env_add(all, "PWD=", getcwd(buf, 1024));
	return(0);
}

void	cd(t_all *all)
{
	t_list	*env;

	if (all->token->args[1] == NULL)
	{
		env = env_srh(all, "HOME=");
		if (env != NULL)
			move_path(all, &env->content[5]);
		else
			error_message("HOME not set", all);
	}
	else if (ft_strncmp(all->token->args[1], "-", 1) == 0)
	{
		env = env_srh(all, "OLDPWD=");
		if (env != NULL)
			move_path(all, &env->content[7]);
		else
			error_message("OLDPWD not set", all);
	}
	else
		move_path(all, all->token->args[1]);
	// ft_pwd();
	// printf_env(all);
}