/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:55:43 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/21 11:57:26by hcshelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	buf = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1 || !s2 || !buf)
		return (NULL);
	while (s1[i])
	{
		buf[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		buf[j] = s2[i];
		j++;
		i++;
	}
	buf[j] = '\0';
	return (buf);
}
