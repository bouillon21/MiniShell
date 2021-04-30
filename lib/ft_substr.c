/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:33:11 by cshelli           #+#    #+#             */
/*   Updated: 2021/04/30 21:59:03 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	i;

	i = 0;
	buf = (char *)ft_calloc(sizeof(char *), (len + 1));
	if (!s || !buf)
		return (0);
	if (start >= ft_strlen((char *)s))
	{
		buf[0] = '\0';
		return (buf);
	}
	while (s[start] && i < len)
	{
		buf[i] = s[start];
		i++;
		start++;
	}
	buf[i] = '\0';
	return (buf);
}
