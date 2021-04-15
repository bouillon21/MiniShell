#include "minishell.h"

void	sort_export(t_list *export)// не по норме +5
{
	t_list *copy;
	t_list *next;
	char *tmp;

	copy = export;
	if (export)
		next = export->next;
	while (copy)
	{
		while (next)
		{
			if (ft_strcmp(copy->content->key, next->content->key) > 0)
			{
				tmp = copy->content->key;
				copy->content->key = next->content->key;
				next->content->key = tmp;
				tmp = copy->content->value;
				copy->content->value = next->content->value;
				next->content->value = tmp;
			}
			next = next->next;
		}
		copy = copy->next;
		next = copy;
	}
}

void	print_export(t_list *env)
{
	t_list	*head;
	t_list	*export;

	export = copy_list(env);
	head = export;
	sort_export(export);
	while(export)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(export->content->key, 1);
		if (export->content->value)
		{
			ft_putstr_fd("=\"", 1);
			printf("%s\"\n", export->content->value);
		}
		else
			ft_putstr_fd("\n", 1);
		export = export->next;
	}
	ft_lstclear(&head, &free);
}

int	valid_export(char *arg)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return(-1);
	while (arg[++i] && arg[i] != '=')
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+') || flag)
			return(-1);
		if (arg[i] == '+')
			flag = 1;
	}
	return(0);
}

void	ft_uset(t_all *all)
{
	int	i;
	int	flag;
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
				if (flag)
					env->next = tmp->next;
				else
					all->env = tmp->next;
				free(tmp->content->key);
				free(tmp->content->value);
				free(tmp->content);
				free(tmp);
				break;
			}
			flag = 1;
			env = tmp;
			tmp = tmp->next;
		}
	}
}

void	export(t_all *all)//  не по норме +3 строки
{
	int	i;
	char	*line;
	char	**tmp;

	i = 0;
	if (all->token->args[1] == NULL)
		print_export(all->env);
	else
	{
		while (all->token->args[++i])
		{
			if (valid_export(all->token->args[i]))
			{
				line = ft_strjoin(all->token->args[i], ": not a valid identifier");
				error_message(line, all);
				free(line);
			}
			else if (ft_strnstr(all->token->args[i], "+=" , ft_strlen(all->token->args[i])))
			{
				tmp = separation_line(all->token->args[i]);
				if (env_srh(all, tmp[0]) && env_srh(all, tmp[0])->content->value != NULL)
				{
					line = ft_strjoin(env_srh(all, tmp[0])->content->value, tmp[1]);
					env_add(all, tmp[0], line);
					free(line);
				}
				else
					env_add(all, tmp[0], tmp[1]);
				free_array(&tmp);
			}
			else if (ft_strchr(all->token->args[i], '=') != NULL)
			{
				tmp = separation_line(all->token->args[i]);
				env_add(all, tmp[0], tmp[1]);
				free_array(&tmp);
			}
			else
				if (env_srh(all, all->token->args[i]) == NULL)
					env_add(all, all->token->args[i], NULL);
		}
	}
}