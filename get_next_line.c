/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 21:15:30 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/05 21:15:19 by kboonkos         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	ssize_t				byte_read;
	static t_list		*stash;
	t_list				*node;
	char				*buf;
	char				*res;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	byte_read = 0;
	node = stash;
	res = NULL;
	while (res == NULL)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(buf), NULL);
		else if (byte_read == 0)
		{
			if (stash == NULL)
				return (free(buf), NULL);
			size_t count = 0;
			node = stash;
			while (node != NULL)
			{
				count += ft_strlen(node->content);
				node = node->next;
			}
			res = malloc(sizeof(char) * (count + 1));
			node = stash;
			char	*ptr = res;
			size_t	index = 0;
			while (node->next != NULL)
			{
				ft_memcpy(&ptr[index * BUFFER_SIZE],
					node->content, BUFFER_SIZE);
				node = node->next;
				++index;
			}
			ft_memcpy(&ptr[index * BUFFER_SIZE], node->content,
				(ft_strlen(node->content)));	// Fix last node always null
			*(res + count) = '\0';
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
		else
		{
			buf[byte_read] = '\0';
			ft_lstadd_back(&stash, ft_lstnew(ft_strdup(buf)));
			if (ft_strchr(buf, DELIMITER) != NULL)
			{
				size_t count = 0;
				node = stash;
				while (node != NULL)
				{
					count += ft_strlen(node->content);
					node = node->next;
				}
				res = malloc(sizeof(char) * (count + 1));
				node = stash;
				char	*ptr = res;
				size_t	offset = 0;
				while (node->next != NULL)
				{
					ft_memcpy(&ptr[offset],
						node->content, ft_strlen(node->content);
					offset += ft_strlen(node->content);
					node = node->next;
				}
				ft_memcpy(&ptr[offset], node->content,
					(((char *)(ft_strchr(node->content, DELIMITER))) -
					(char *)(node->content) + 1
					));
				*(res + count) = '\0';
				char	*tail = ft_strdup(ft_strchr(node->content,
					DELIMITER) + 1);
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
		}
	}
	free(buf);
	return (res);
}
