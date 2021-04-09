/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:55:36 by cshelli           #+#    #+#             */
/*   Updated: 2021/04/07 18:31:14 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		n;
	char	*buf;

	n = 0;
	if (!src)
		return (ft_strdup(""));
	buf = (char *)malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!buf)
		return (0);
	while (src[n])
	{
		buf[n] = src[n];
		n++;
	}
	buf[n] = '\0';
	return (buf);
}