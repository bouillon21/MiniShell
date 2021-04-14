/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:37:49 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/14 03:39:25 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_space(int start, char *str)
{
	int i;

	i = start;
	while (str[i] == ' ')
		delete_from_array(i, str);
	return (start);
}

int		ecranisation(int start)
{
	return (++start);
}

int		double_quote_start(int start, char *str)
{
	delete_from_array(start, str);
	while (str[start] != '\"')
	{
		if (str[start] == '$')
			;								//	ТУТ БУДЕТ ВЫТАСКИВАТЬСЯ ТО, ЧТО ЛЕЖИТ В $
		start++;
		if (str[start] == '\n')
			exit(0);						// ТУТ СДЕЛАТЬ ОШИБКУ!! ЪУЪ!!!!
	}
	delete_from_array(start, str);
	return (start);
}

int		single_quote_start(int start, char *str)
{
	delete_from_array(start, str);
	while (str[start] != '\'')
	{
		start++;
		if (str[start] == '\n')
			exit(0);						// ТУТ СДЕЛАТЬ ОШИБКУ!! ЪУЪ!!!!
	}
	delete_from_array(start, str);
	return (++start);
}