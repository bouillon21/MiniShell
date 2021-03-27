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

char	**env_srh(t_list **env, char *need)
{
	t_list	*head;

	head = *env;
	while (head->next)
	{
		if (ft_strnstr(head->content, need, ft_strlen(need)))
			return(&head->content);
		head = head->next;
	}
	return(NULL);
}

void	printf_env(t_list *head)
{
	while (head->next)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
}