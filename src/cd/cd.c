#include "minishell.h"

void	save_old_pwd(t_list **env)
{
	char	*line;
	char	*buf;
	
	buf = malloc(1024);
	getcwd(buf, 1024);
	if (env_srh_edit(env, "OLDPWD=", buf) == NULL)
		ft_lstadd_back(env, ft_lstnew(buf));
	free(buf);
}

int	move_path(t_list **env, char *arg)
{
	char	*buf;
	char	*new_path;

	buf = malloc(1024);
	new_path = env_srh_edit(env,arg, NULL);
	printf("%s\n", new_path);
	if (new_path == NULL)
		return (-1);
	save_old_pwd(env);
	chdir(new_path);
	getcwd(buf, 1024);
	env_srh_edit(env, "PWD=", buf);
	free(buf);
	return(0);
}

void	cd(t_list **env, char *arg)
{
	if (arg == NULL)
	{
		move_path(env, "HOME=");
	}
	// else if	(ft_strncmp(arg, "-", 1) == 0)
	// {
	// 	move_path(env, "OLDPWD=");
	// }
	else
	{
		move_path(env, arg);
	}
}