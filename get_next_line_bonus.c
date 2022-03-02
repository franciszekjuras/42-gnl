/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:01:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/02 11:59:12 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

t_list	*list_add(t_list *prev, int id, char *str, size_t size);
// t_list	*list_find(t_list *prev, int id);
void	list_remove(t_list *prev);
void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen_null(const char *s);
int		ft_strnsplit(char *str, char **s1_p, char **s2_p, size_t n);

/**
 * @brief Return `buf` appended to `str`, allocating and deallocating
 * memory as necessary. If `str` is null it's treated as empty.
 * Always return a valid string except of malloc error.
 * 
 * @param str string to append to
 * @param buf buffer with string to append
 * @return char* pointer to appended string
 */
static int	node_appbuf(t_list *node, const char *buf)
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

static t_list	*process_buffered(t_list *root, int fd, size_t *i_p)
{
	t_list	*node;
	size_t	i;

	node = root->next;
	while (node != 0 && node->id != fd)
		node = node->next;
	i = 0;
	if (node == 0)
		node = list_add(root, fd, 0, 0);
	else if (node->str != 0)
		while (node->str[i] != '\0' && node->str[i] != '\n')
			i++;
	*i_p = i;
	return (node);
}

static char	*parse_line(t_list *root, t_list *node, size_t i)
{
	char	*line;
	char	*rest;

	if (node->str[i] != '\0')
		i++;
	if (i == 0)
	{
		while (root->next != 0 && root->next->id != node->id)
			root = root->next;
		list_remove(root);
		return (0);
	}
	rest = 0;
	if (!ft_strnsplit(node->str, &line, &rest, i))
		return (0);
	node->str = rest;
	node->size = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	root = {0, 0, 0, 0};
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
		if(!node_appbuf(node, buf))
			return (0);
		while (node->str[i] != '\0' && node->str[i] != '\n')
			i++;
	}
	return (parse_line(&root, node, i));
}
