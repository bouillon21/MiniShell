/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_bs_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:42:40 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/31 19:50:50 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_from_array(int i)
{
	while (g_string[i + 1])
	{
		g_string[i] = g_string[i + 1];
		i++;
	}
	g_string[i] = 0;
}