#include "minishell.h"

void	get_save_env(t_all *all, char **envp)
{
	int		i;
	char	*tmp;
	t_env_data	*data;

	i = 0;
	while (envp && envp[i])
	{
		data = ft_calloc(sizeof(t_env_data),1);
		data->key = ft_substr(envp[i], 0,
			ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '=')));
		data->value = NULL;
		tmp = ft_strchr(envp[i], '=');
		if (tmp)
			data->value = ft_strdup(tmp + 1);
		ft_lstadd_back(&all->env, ft_lstnew(data));
		i++;
	}
	if (env_srh(all, "HOME"))
		all->static_home = ft_strdup(env_srh(all, "HOME")->content->value);
	env_add(all, "OLDPWD", NULL);
}

t_list	*env_srh(t_all	*all, char *need)
{
	t_list	*env;

	env = all->env;
	while (env)
	{
		if (ft_strncmp(env->content->key, need, ft_strlen(need)) == 0)
			return(env);
		env = env->next;
	}
	return(NULL);
}

void	env_add(t_all *all, char *need, char *content)
{
	t_list	*env;
	t_env_data	*data;

	env = env_srh(all, need);
	if(env == NULL)
	{
		data = malloc(sizeof(t_env_data));
		data->key = ft_strdup(need);
		data->value = NULL;
		if (content)
			data->value = ft_strdup(content);
		ft_lstadd_back(&all->env, ft_lstnew(data));
	}
	else
	{
		free(env->content->value);
		if (content != NULL)
			env->content->value = ft_strdup(content);
		else
			env->content->value = NULL;
	}
}

char	**env_join(t_list *env)
{
	int	i;
	char	**env_copy;
	char	*tmp;

	i = 0;
	env_copy = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	if (!env_copy)
		return (NULL);
	while (env)
	{
		if (env->content->value)
		{
			tmp = ft_strjoin("=", env->content->value);
			env_copy[i] = ft_strjoin(env->content->key, tmp);
			free (tmp);
			i++;
		}
		env = env->next;
	}
	return (env_copy);
}

void	printf_env(t_all *all)
{
	t_list	*env;

	env = all->env;
	while (env)
	{
		if (env->content->value)
			printf("%s=%s\n", env->content->key, env->content->value);
		env = env->next;
	}
}