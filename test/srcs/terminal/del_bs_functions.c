/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_bs_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:42:40 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/28 10:04:31 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

void	delete_symbol(t_all *all)
{
	int	i;

	i = all->cursor.current_pos - all->cursor.start_pos;
	if (all->cursor.current_pos == all->cursor.end_pos)
		g_string[i] = '\0';
}