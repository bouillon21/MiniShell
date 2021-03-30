#include "minishell.h"

void	get_save_env(t_list **head ,char **envp)
{
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}

char	*env_srh(t_list **env, char *need)
{
	int	i;
	t_list	*head;

	i = 0;
	head = *env;
	while (head->next)
	{
		if (ft_strnstr(head->content, need, ft_strlen(need)))
			return(ft_strrchr(head->content,'=') + 1);
		head = head->next;
	}
	return("");
}

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

void	printf_env(t_list *head)
{
	while (head->next)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
	printf("%s\n", head->content);
}