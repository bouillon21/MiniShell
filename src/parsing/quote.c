/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:37:49 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/01 22:31:42 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_space(int start)
{
	if (g_string[start])
		while (g_string[start] == ' ')
			delete_from_array(start);
	return (start);
}

int		ecranisation(int start)
{
	return (++start);
}

int		double_quote_start(int start)
{
	while (g_string[start] != '\"')
	{
		if (g_string[start] == '$')
			;								//	ТУТ БУДЕТ ВЫТАСКИВАТЬСЯ ТО, ЧТО ЛЕЖИТ В $
		start++;
		if (g_string[start] == '\n')
			exit(0);						// ТУТ СДЕЛАТЬ ОШИБКУ!! ЪУЪ!!!!
	}
	delete_from_array(start);
	return (start);
}

int		single_quote_start(int start)
{
	while (g_string[start] != '\'')
	{
		start++;
		if (g_string[start] == '\n')
			exit(0);						// ТУТ СДЕЛАТЬ ОШИБКУ!! ЪУЪ!!!!
	}
	delete_from_array(start);
	return (++start);
}