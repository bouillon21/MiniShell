#include "minishell.h"

void	string_to_lower(char **mas)
{
	int i;

	i = -1;
	while (mas[0][++i] != 0)
		mas[0][i] = ft_tolower(mas[0][i]);
}

void	free_array(char ***mas)
{
	int	i;

	i = 0;
	while ((*mas)[i])
	{
		free((*mas)[i]);
		i++;
	}
	free(*mas);
}

char	**separation_line(char *line)
{
	char **mas;
	int	len;

	mas = ft_calloc(sizeof(char *), 3);
	len = ft_strlen(line) - ft_strlen(ft_strchr(line, '='));
	if (ft_strnstr(line, "+=", ft_strlen(line)))
		len--;
	mas[0] = ft_substr(line, 0, len);
	if ((ft_strchr(line, '=') + 1) != NULL)
		mas[1] = ft_strdup(ft_strchr(line, '=') + 1);
	else
		mas[1] = ft_strdup("");
	return(mas);
}

t_list	*copy_list(t_list *env)
{
	t_list	*export;
	t_env_data	*data;

	export = NULL;
	while (env)
	{
		data = (t_env_data *)ft_calloc(sizeof(t_env_data), 1);
		data->key = ft_strdup(env->content->key);
		data->value = NULL;
		if (env->content->value)
			data->value = ft_strdup(env->content->value);
		ft_lstadd_back(&export, ft_lstnew(data));
		env = env->next;
	}
	return (export);
}
