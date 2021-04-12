#include "minishell.h"

int	move_path(t_all *all, char *path)
{
	char	buf[1024];

	env_add(all, "OLDPWD", getcwd(buf, 1024));
	if (chdir(path) == -1)
	{
		error_message("No such file or directory", all);
		return(-1);
	}
	env_add(all, "PWD", getcwd(buf, 1024));
	return(0);
}

void	cd(t_all *all)
{
	t_list	*env;
	char	buf[1024];

	if (all->token->args[1] == NULL)
	{
		env = env_srh(all, "HOME");
		if (env != NULL)
			move_path(all, env->content->value);
		else
			error_message("HOME not set", all);
	}
	else if (ft_strncmp(all->token->args[1], "-", 1) == 0)
	{
		env = env_srh(all, "OLDPWD");
		if (env->content->value != NULL)
		{
			move_path(all, env->content->value);
			printf("%s\n", getcwd(buf, 1024));
		}
		else
			error_message("OLDPWD not set", all);
	}
	else
		move_path(all, all->token->args[1]);
}