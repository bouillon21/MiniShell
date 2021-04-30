#include "minishell.h"

void	clear_tmp(t_list *tmp, t_list *env, t_all *all, int flag)
{
	if (flag)
		env->next = tmp->next;
	else
		all->env = tmp->next;
	free(tmp->content->key);
	free(tmp->content->value);
	free(tmp->content);
	free(tmp);
}

void	ft_uset(t_all *all)
{
	int		i;
	int		flag;
	t_list	*env;
	t_list	*tmp;

	i = 0;
	while (all->token->args[++i])
	{
		flag = 0;
		env = all->env;
		tmp = env;
		while (tmp)
		{
			if (ft_strcmp(tmp->content->key, all->token->args[i]) == 0)
			{
				clear_tmp(tmp, env, all, flag);
				break ;
			}
			flag = 1;
			env = tmp;
			tmp = tmp->next;
		}
	}
}
