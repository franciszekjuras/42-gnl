/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:01:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/02 22:24:10 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen_null(const char *s);
char	*ft_strnsplit(char *str, size_t n);

/**
 * @brief Append `buf` to `node->str`, allocating and deallocating
 * memory as necessary. If `node->str` is null it's treated as empty.
 * After calling this function, node->str will be a valid string
 * except of a malloc error 
 * @param node node with string for appending
 * @param buf buffer with string to append
 * @return int 1 on success, 0 on failure
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

/**
 * @brief Check for buffered data from file descriptor `fd`.
 * Return appropriate list node (creating it if necessary)
 * and set value addressed by `i_p` to the first newline in the buffer
 * or its end. 
 * @param root root of a list
 * @param fd file descriptor
 * @param i_p pointer for storing position of newline or end of buffer
 * @return t_list* pointer to node corresponding to `fd`
 */
static t_list	*process_buffered(t_list *root, int fd, size_t *i_p)
{
	t_list	*node;
	size_t	i;

	node = root->next;
	while (node != 0 && node->id != fd)
		node = node->next;
	i = 0;
	if (node == 0)
	{
		node = malloc(sizeof(t_list));
		if (node == 0)
			return (0);
		node->id = fd;
		node->str = 0;
		node->size = 0;
		node->next = root->next;
		root->next = node;
	}
	else if (node->str != 0)
		while (node->str[i] != '\0' && node->str[i] != '\n')
			i++;
	*i_p = i;
	return (node);
}

static char	*close_fd(t_list *root, int fd)
{
	t_list	*next;
	
	while (root->next != 0 && root->next->id != fd)
		root = root->next;
	next = root->next;
	root->next = next->next;
	free(next->str);
	free(next);
	return (0);
}

/**
 * @brief Split, allocate and return line from `node->str`.
 * If end of file was reached, remove node and return null. 
 * @param root root of a list
 * @param node node in a list
 * @param i position of end of lint
 * @return char* allocated line
 */
static char	*parse_line(t_list *root, t_list *node, size_t i)
{
	char	*line;
	
	if (node->str[i] != '\0')
		i++;
	if (i == 0)
		return (close_fd(root, node->id));
	line = ft_strnsplit(node->str, i);
	if (line == 0)
		return (close_fd(root, node->id));
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
	if (node == 0)
		return (0);
	char_read = -1;
	while ((node->str == 0 || node->str[i] != '\n') && char_read != 0)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
			return (close_fd(&root, fd));
		buf[char_read] = '\0';
		if(!node_appbuf(node, buf))
			return (close_fd(&root, fd));
		while (node->str[i] != '\0' && node->str[i] != '\n')
			i++;
	}
	return (parse_line(&root, node, i));
}
