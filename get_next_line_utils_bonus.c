/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:14:11 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/02 12:01:15 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

/**
 * @brief Allocate and add list node after `prev`
 * @param prev node in a list
 * @param id parameteter to initialize new node
 * @param str parameteter to initialize new node
 * @return t_list* pointer to newly created list node or null on error
 */
t_list	*list_add(t_list *prev, int id, char *str, size_t size)
{
	t_list	*next;

	next = malloc(sizeof(t_list));
	if (next == 0)
		return (0);
	next->id = id;
	next->str = str;
	next->size = size;
	next->next = prev->next;
	prev->next = next;
	return (next);
}

/**
 * @brief Find element with id `id` and return element before.
 * @param root root of the list (root is not searched)
 * @param id id to search for
 * @return t_list* pointer to element **before** the found node 
 * or last element if `id` was not found
 */
// t_list	*list_find(t_list *root, int id)
// {
// 	t_list	*prev;

// 	prev = root;
// 	while (prev->next != 0 && prev->next->id != id)
// 		prev = prev->next;
// 	return (prev);
// }

/**
 * @brief Remove node after `prev` or do nothing if prev->next is null.
 * 
 * @param prev list node **before** the one to remove
 */
void	list_remove(t_list *prev)
{
	t_list	*next;

	if (prev->next == 0)
		return ;
	next = prev->next;
	prev->next = next->next;
	free(next->str);
	free(next);
}

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

int	ft_strnsplit(char *str, char **s1_p, char **s2_p, size_t n)
{
	size_t	s2_len;
	char	*s1;
	char	*s2;

	s2_len = ft_strlen_null(str + n);
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
