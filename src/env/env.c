#include "minishell.h"

void	get_save_env(t_all *all, char **envp)
{
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		ft_lstadd_back(&all->env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	env_add(all, "OLDPWD", NULL);
}

t_list	*env_srh(t_all	*all, char *need)
{
	t_list	*env;

	env = all->env;
	while (env->next)
	{
		if (ft_strnstr(env->content, need, ft_strlen(need)))
			return(env);
		env = env->next;
	}
	return(NULL);
}

void	env_add(t_all *all, char *need, char *content)
{
	t_list	*env;
	char	*line;

	env = env_srh(all, need);
	if(env != NULL)
	{
		free(env->content);
		if (content != NULL)
			line = ft_strjoin(need, content);
		else
			line = ft_strjoin(need, "");
		env->content = ft_strdup(line);
		free(line);
	}
	else
	{
		line = ft_strjoin(need, content);
		ft_lstadd_back(&all->env, ft_lstnew(ft_strdup(line)));
		free(line);
	}
}

char	**env_join(t_list *env)
{
	int	i;
	char	**env_copy;
	
	i = 0;
	env_copy = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	if (!env_copy)
		return (NULL);
	while (env->next)
	{
		env_copy[i] = ft_strdup(env->content);
		env = env->next;
		i++;
	}
	env_copy[i] = ft_strdup(env->content);
	env_copy[++i] = NULL;
	return (env_copy);
}

void	printf_env(t_all *all)
{
	t_list	*env;

	env = all->env;
	while (env->next)
	{
		if (ft_strchr(env->content, '=') != 0)
			printf("%s\n", env->content);
		env = env->next;
	}
		if (ft_strchr(env->content, '=') != 0)
			printf("%s\n", env->content);
}