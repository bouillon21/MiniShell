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

char	*env_srh_edit(t_list **env, char *need, char *changes)
{
	t_list	*head;

	head = *env;
	while (head->next)
	{
		if (ft_strnstr(head->content, need, ft_strlen(need)))
		{
			if (changes == NULL)
				return(ft_strrchr(head->content,'=') + 1);
			free(head->content);
			changes = ft_strjoin(need, changes);
			head->content = ft_strdup(changes);
			free(changes);
			return(head->content);
		}
		head = head->next;
	}
	return(NULL);
}

char	**env_join(t_list *env)
{
	int	i;
	char	**env_copy;
	
	i = 0;
	env_copy = malloc(sizeof(char *) * ft_lstsize(env) + 1);
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

void	printf_env(t_list *head)
{
	while (head->next)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
	printf("%s\n", head->content);
}