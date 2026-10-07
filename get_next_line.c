/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 17:08:16 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/08 03:57:05 by kboonkos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif
#define DELIMITER '\n'

static size_t	line_len(const char *s)
{
	char	*nl;

	nl = ft_strchr(s, '\n');
	if (nl)
		return (nl - s + 1);
	return (ft_strlen(s));
}

int	fill_stash(int fd, t_list **stash)
{
	char	*buf;
	int		byte_read;

	if (*stash && ft_strchr((*stash)->content, '\n'))
		return (1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	while (1)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(buf), 0);
		else if (byte_read == 0)
			break ;
		buf[byte_read] = '\0';
		if (lst_append(stash, ft_strdup(buf)) == 0)
			return (free(buf), lst_clear(stash), 0);
		if (ft_strchr(buf, '\n') != 0)
			break ;
	}
	free(buf);
	return (1);
}

size_t	stash_len(t_list *stash)
{
	size_t	len;

	len = 0;
	while (stash != NULL)
	{
		len += line_len(stash->content);
		stash = stash->next;
	}
	return (len);
}

char	*build_line(t_list *stash)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*line;

	line = malloc(sizeof(char *) * (stash_len(stash) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash != NULL)
	{
		j = 0;
		k = line_len(stash->content);
		while (j < k)
			line[i++] = ((char *)(stash->content))[j++];
		stash = stash->next;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;
	char			*tail;
	t_list			*node;

	if ((fd < 0) || (BUFFER_SIZE < 1))
		return (NULL);
	if ((fill_stash(fd, &stash) == 0) || (stash == NULL))
		return (lst_clear(&stash), NULL);
	line = build_line(stash);
	node = stash;
	while (node->next != NULL)
		node = node->next;
	tail = ft_strdup((char *)(node->content) + line_len(node->content));
	lst_clear(&stash);
	if (!line || !tail || !*tail)
		return (free(tail), line);
	else if (lst_append(&stash, tail) == 0)
		return (free(line), NULL);
	else
		return (line);
}
// !*tail checks, at EOF, when the newline is the last byte of a node,
// tail is "", a valid empty string so it gets appended as a node.
// On the next call fill_stash reads 0 bytes, but the stash isn't empty.
// build_line() then returns "" instead of NULL.
