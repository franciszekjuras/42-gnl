/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:14:11 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/02 22:39:30 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

/**
 * @brief Copy `len` bytes from `src` to `dst`, which may overlap. 
 * @param dst copy destination address
 * @param src copy destination source
 * @param len number of bytes to copy
 * @return void* pointer to destination
 */
void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (dst > src)
	{
		while (i < len)
		{
			d[len - i - 1] = s[len - i - 1];
			i++;
		}
	}
	return (dst);
}

/**
 * @brief Return length of string `s` or 0 if `s` is null. 
 * @param s string
 * @return size_t string length
 */
size_t	ft_strlen_null(const char *s)
{
	size_t	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief Split string `str` into strings with `n` and `strlen(str) - n`
 * characters. Allocate and return copy of the first string.
 * Move second string into the beggining of `str`. 
 * @param str string to split
 * @param n index to split at
 * @return char* pointer to newly allocated first string (null on malloc error)
 */
char	*ft_strnsplit(char *str, size_t n)
{
	size_t	trail_len;
	char	*lead_str;

	trail_len = ft_strlen_null(str + n);
	lead_str = malloc(sizeof(char) * (n + 1));
	if (lead_str == 0)
		return (0);
	ft_memcpy(lead_str, str, n);
	lead_str[n] = '\0';
	ft_memcpy(str, str + n, trail_len + 1);
	return (lead_str);
}
