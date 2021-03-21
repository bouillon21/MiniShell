/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 19:03:16 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/21 11:58:35 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		count;
	char	*buf;

	count = 0;
	buf = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s || !f || !buf)
		return (0);
	while (s[count])
	{
		buf[count] = f((unsigned char)count, s[count]);
		count++;
	}
	buf[count] = '\0';
	return (buf);
}
