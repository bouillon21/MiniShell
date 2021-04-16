/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 04:26:52 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/16 06:41:41 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_dollar(char *str, int i, t_all *all)
{
	char	*value;
	char	*tmp;
	int		j;
	int		diff;
	t_list	*tmp_list;

	j = i;
	if (ft_isdigit(str[i]))
		return (NULL);
	while (ft_isalnum(str[i]))
		i++;
	diff = i - j;
	tmp = ft_substr(str, j, i - j);
	tmp_list = env_srh(all, tmp);
	free(tmp);
	while (diff-- > 0)
		delete_from_array(j, str);
	if (!tmp_list)
		return (ft_strdup(""));
	return (ft_strdup(tmp_list->content->value));
}

int	double_quote_start(int start, t_all *all)
{
	char	*insert;

	delete_from_array(start, all->string);
	while (all->string[start] != '\"')
	{
		if (all->string[start] == '$' && (all->string[start + 1] != '\n'
				|| all->string[start + 1] != ' '))
		{
			delete_from_array(start, all->string);
			insert = parse_dollar(all->string, start, all);
			if (insert)
				insert_inside(insert, start, all, 0);
			start += ft_strlen(insert) - 2;
			free(insert);
		}
		start++;
	}
	delete_from_array(start, all->string);
	return (start);
}
