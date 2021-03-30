/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:37:49 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/30 21:12:43 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int		skip_space(int start)
{
	while (g_string[start] == ' ')
		start++;
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
		start++;
		if (g_string[start] == '\n')
			exit(0);						// ТУТ СДЕЛАТЬ ОШИБКУ!! ЪУЪ!!!!
	}
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
	return (start);
}