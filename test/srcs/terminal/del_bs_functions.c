/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_bs_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:42:40 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/27 16:40:34 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

void	delete_symbol(t_all *all)
{
	int	i;

	i = all->cursor.cursor_current_pos - all->cursor.cursor_start_pos;
	if (all->cursor.cursor_current_pos == all->cursor.cursor_end_pos)
		all->tmp_string[i] = '\0';
}