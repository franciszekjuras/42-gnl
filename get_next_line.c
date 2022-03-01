/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:01:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/01 22:03:56 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

t_list	*list_add(t_list *prev, int id, char *str);
t_list	*list_find(t_list *prev, int id);
void	list_remove(t_list *prev);
void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *s);

/**
 * @brief Return `buf` appended to `str`, allocating and deallocating
 * memory as necessary. If `str` is null it's treated as empty.
 * Always return a valid string except of malloc error.
 * 
 * @param str string to append to
 * @param buf buffer with string to append
 * @return char* pointer to appended string
 */
static char	*ft_strappbuf(char *str, const char *buf)
{
	char	*dst;
	size_t	str_len;
	size_t	buf_len;

	if (buf[0] == '\0' && str != 0)
		return ((char *) str);
	if (str != 0)
		str_len = ft_strlen(str);
	else
		str_len = 0;
	buf_len = ft_strlen(buf);
	dst = malloc(str_len + buf_len + 1);
	if (dst == 0)
		return (0);
	ft_memcpy(dst, str, str_len);
	ft_memcpy(dst + str_len, buf, buf_len + 1);
	if (str != 0)
		free(str);
	return (dst);
}

static t_list	*process_buffered(t_list *root, int fd, size_t *i_p)
{
	t_list	*node;
	size_t	i;

	node = list_find(root, fd)->next;
	i = 0;
	if (node == 0)
		node = list_add(root, fd, 0);
	else if (node->str != 0)
		while (node->str[i] != '\0' && node->str[i] != '\n')
			i++;
	*i_p = i;
	return (node);
}

static int	ft_strnsplit(char *str, char **s1_p, char **s2_p, size_t n)
{
	size_t	s2_len;
	char	*s1;
	char	*s2;

	s2_len = ft_strlen(str + n);
	if (s2_len == 0)
	{
		*s1_p = str;
		return (1);
	}
	s1 = malloc(sizeof(char) * (n + 1));
	s2 = malloc(sizeof(char) * (s2_len + 1));
	if (s1 == 0 || s2 == 0)
	{
		free(s1);
		free(s2);
		return (0);
	}
	ft_memcpy(s1, str, n);
	s1[n] = '\0';
	ft_memcpy(s2, str + n, s2_len + 1);
	*s1_p = s1;
	*s2_p = s2;
	free(str);
	return (1);
}

static char	*parse_line(t_list *root, t_list *node, size_t i)
{
	char	*line;
	char	*rest;


	if (node->str[i] != '\0')
		i++;
	if (i == 0)
	{
		list_remove(list_find(root, node->id));
		return (0);
	}
	rest = 0;
	if (!ft_strnsplit(node->str, &line, &rest, i))
		return (0);
	node->str = rest;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	root = {0};
	t_list			*node;
	char			buf[BUFFER_SIZE + 1];
	ssize_t			char_read;
	size_t			i;

	node = process_buffered(&root, fd, &i);
	char_read = -1;
	while ((node->str == 0 || node->str[i] != '\n') && char_read != 0)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
			return (0);
		buf[char_read] = '\0';
		node->str = ft_strappbuf(node->str, buf);
		while (node->str[i] != '\0' && node->str[i] != '\n')
			i++;
	}
	return (parse_line(&root, node, i));
}
