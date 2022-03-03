/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:03:48 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/03 11:32:02 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stddef.h>

/*
#include <stdio.h>
#include <stdlib.h>
int	incr(int inc);

static void	*xmalloc(unsigned int size)
{
	void		*ptr;

	if (incr(-1) == 0)
		ptr = 0;
	else
		ptr = malloc(size);
	fprintf(stderr, "malloc:%p\n", ptr);
	return (ptr);
}

static void	xfree(void *ptr)
{
	fprintf(stderr, "free  :%p\n", ptr);
	free(ptr);
}

#define malloc(x) xmalloc(x)
#define free(x) xfree(x)
*/

char	*get_next_line(int fd);
void	*gnl_close(int fd);

typedef struct s_list	t_list;

struct s_list
{
	int		id;
	char	*str;
	size_t	size;
	t_list	*next;
};

#endif
