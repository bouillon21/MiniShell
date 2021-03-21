/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:15:34 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/21 11:34:00 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destptr, const void *srcptr, int c, size_t num)
{
	size_t	i;

	i = 0;
	if (!destptr && !srcptr)
		return (NULL);
	while (i < num)
	{
		((char *)destptr)[i] = ((char *)srcptr)[i];
		if (((unsigned char *)srcptr)[i] == (unsigned char)c)
			return ((unsigned char *)destptr + i + 1);
		i++;
	}
	return (0);
}
