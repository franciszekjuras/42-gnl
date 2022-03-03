/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:14:11 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/03 11:53:40 by fjuras           ###   ########.fr       */
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

/**
 * @brief Append `buf` to `node->str`, allocating and deallocating
 * memory as necessary. If `node->str` is null it's treated as empty.
 * After calling this function, node->str will be a valid string
 * except of a malloc error 
 * @param node node with string for appending
 * @param buf buffer with string to append
 * @return int 1 on success, 0 on failure
 */
int	node_appbuf(t_list *node, const char *buf)
{
	char	*dst;
	size_t	str_len;
	size_t	buf_len;

	if (buf[0] == '\0' && node->str != 0)
		return (1);
	str_len = ft_strlen_null(node->str);
	buf_len = ft_strlen_null(buf);
	if (node->size < str_len + buf_len + 1)
	{
		dst = malloc((str_len * 2) + buf_len + 1);
		if (dst == 0)
			return (0);
		ft_memcpy(dst + str_len, buf, buf_len + 1);
		ft_memcpy(dst, node->str, str_len);
		free(node->str);
		node->str = dst;
		node->size = (str_len * 2) + buf_len + 1;
	}
	else
		ft_memcpy(node->str + str_len, buf, buf_len + 1);
	return (1);
}
