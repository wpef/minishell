/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 18:15:22 by fde-monc          #+#    #+#             */
/*   Updated: 2015/12/04 18:23:12 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	while (dst[i] && i < size)
		i++;
	dst_len = i;
	while (src[i - dst_len] && i < size - 1)
	{
		dst[i] = src[i - dst_len];
		i++;
	}
	if (dst_len < size)
		dst[i] = '\0';
	return (dst_len + ft_strlen(src));
}
