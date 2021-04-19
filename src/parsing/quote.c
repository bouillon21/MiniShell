/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:37:49 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/16 05:25:55 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(int start, char *str)
{
	int	i;

	i = start;
	while (str[i] == ' ')
		delete_from_array(i, str);
	return (start);
}

int	ecranisation(int start, char *str)
{
	delete_from_array(start, str);
	return (start);
}

int	single_quote_start(int start, char *str)
{
	delete_from_array(start, str);
	while (str[start] != '\'')
		start++;
	delete_from_array(start, str);
	return (start);
}
