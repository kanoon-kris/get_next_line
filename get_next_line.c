/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 17:08:16 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/06 21:39:47 by kboonkos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif
#define DELIMITER '\n'

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_copy;
	unsigned char		*dest_copy;

	src_copy = src;
	dest_copy = dest;
	while (n--)
		*dest_copy++ = *src_copy++;
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c_copy;
	size_t			idx;

	c_copy = c;
	idx = 0;
	while (1)
	{
		if ((unsigned char)s[idx] == c_copy)
			return ((char *)(s + idx));
		if (s[idx] == '\0')
			return (NULL);
		++idx;
	}
}

void	clear_preceding_lst(t_list *stash, size_t index)
{
	t_list	*tmp;

	++index;
	while (index != 0)
	{
		tmp = stash->next;
		ft_lstdelone(stash, free);
		stash = tmp;
		--index;
	}
}

void	extract_line(t_list *stash, char *res,
unsigned int is_last_node_entirely_processed)
{
	t_list	*node;
	size_t	count = 0;
	node = stash;
	while (node->next != NULL)
	{
		count += ft_strlen(node->content);
		node = node->next;
	}
	count += (((char *)ft_strchr(node->content, DELIMITER)) -
		(char *)(node->content) + 1);
	res = malloc(sizeof(char) * (count + 1));
	node = stash;
	char	*ptr = res;
	size_t	index = 0;
	size_t	offset = 0;
	while (((!is_last_node_entirely_processed && (node->next != NULL)) ||
		((is_last_node_entirely_processed && (node != NULL)))))
	{
		ft_memcpy(&ptr[offset], node->content, ft_strlen(node->content));
		offset += ft_strlen(node->content);
		node = node->next;
		++index;
	}
	if (!is_last_node_entirely_processed)
		ft_memcpy(&ptr[offset], node->content, (((char *)(ft_strchr(node->content,
		DELIMITER))) - (char *)(node->content) + 1));
	else
		ft_memcpy(&ptr[offset], node->content, (ft_strlen(node->content)));
	*(res + count) = '\0';
	char	*tail = ft_strdup(ft_strchr(node->content, DELIMITER) + 1);
	clear_preceding_lst(stash, index);
	if (is_last_node_entirely_processed)
	{
		if (tail && *tail)
			ft_lstadd_back(&stash, ft_lstnew(tail));
		else
			free(tail);
	}
}

char	*get_next_line(int fd)
{
	char			*buf;
	int				byte_read;
	char			*res;
	static t_list	*stash;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byte_read = 0;
	res = NULL;
	while (res == NULL)
	{
		if (stash != NULL && ft_strchr(stash->content, DELIMITER) != NULL)
			extract_line(stash, res, 0);
		else
		{
			byte_read = read(fd, buf, BUFFER_SIZE);
			if (byte_read < 0)
				return (free(buf), NULL);
			else if (byte_read == 0)
			{
				if (stash == NULL)
					return (free(buf), NULL);
				extract_line(stash, res, 1);
			}
			else
			{
				buf[byte_read] = '\0';
				ft_lstadd_back(&stash, ft_lstnew(ft_strdup(buf)));
				if (ft_strchr(buf, DELIMITER) != NULL)
					extract_line(stash, res, 0);
			}
		}
	}	
	free(buf);
	return (res);
}
