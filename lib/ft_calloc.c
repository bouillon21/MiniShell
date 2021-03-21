/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:50:17 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/21 11:17:41 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*buf;

	buf = (void *)malloc(number * size);
	if (!buf)
		return (0);
	ft_memset(buf, '\0', (number * size));
	return (buf);
}
