/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 17:08:16 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/07 20:24:39 by kboonkos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif
#define DELIMITER '\n'

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

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_node;

	while (*lst)
	{
		next_node = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = next_node;
	}
}

void	extract_line(t_list **stash, char **res)
{
	t_list	*node;
	size_t	count;
	char	*tail;

	tail = NULL;
	count = 0;
	node = *stash;
	while (node->next != NULL)
	{
		count += ft_strlen(node->content);
		node = node->next;
	}
	if (ft_strchr(node->content, DELIMITER) != NULL)
		count += (((char *)ft_strchr(node->content, DELIMITER)) -
			(char *)(node->content) + 1);
	else
		count += ft_strlen(node->content);
	*res = malloc(sizeof(char) * (count + 1));
	node = *stash;
	char	*ptr = *res;
	size_t	offset = 0;
	while (node->next != NULL)
	{
		ft_memcpy(&ptr[offset], node->content, ft_strlen(node->content));
		offset += ft_strlen(node->content);
		node = node->next;
	}
	if (ft_strchr(node->content, DELIMITER) != NULL)
		ft_memcpy(&ptr[offset], node->content, (((char *)(ft_strchr(node->content,
			DELIMITER))) - (char *)(node->content) + 1));
	else
		ft_memcpy(&ptr[offset], node->content, (ft_strlen(node->content)));
	*(*res + count) = '\0';
	if (ft_strchr(node->content, DELIMITER))
		tail = ft_strdup(ft_strchr(node->content, DELIMITER) + 1);
	ft_lstclear(stash, free);
	if (tail && *tail)
		ft_lstadd_back(stash, ft_lstnew(tail));
	else
		free(tail);
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
	res = NULL;
	while (res == NULL)
	{
		if (stash != NULL && ft_strchr(stash->content, DELIMITER) != NULL)
			extract_line(&stash, &res);
		else
		{
			byte_read = read(fd, buf, BUFFER_SIZE);
			if (byte_read < 0)
				return (free(buf), ft_lstclear(&stash, free), NULL);
			else if (byte_read == 0)
			{
				if (stash == NULL)
					return (free(buf), NULL);
				extract_line(&stash, &res);
			}
			else
			{
				buf[byte_read] = '\0';
				ft_lstadd_back(&stash, ft_lstnew(ft_strdup(buf)));
				if (ft_strchr(buf, DELIMITER) != NULL)
					extract_line(&stash, &res);
			}
		}
	}	
	return (free(buf), res);
}
