/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 19:29:45 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/02 02:35:57 by kboonkos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif
#include <stdio.h>

void	clear_lst(void *ptr)
{
	char	*s;

	s = (char *)(ptr);
	free(ptr);
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
	*lst = NULL;
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

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t		count;
	const char	*ptr;

	count = 0;
	ptr = s;
	while (*ptr)
	{
		++count;
		++ptr;
	}
	return (count);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = *lst;
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = new;
}

char	*ft_strdup(const char *s)
{
	size_t				len;
	char				*str_pt;
	const unsigned char	*src_copy;
	unsigned char		*dest_copy;

	len = ft_strlen(s);
	str_pt = malloc(sizeof(char) * len + 1);
	if (str_pt == NULL)
		return (NULL);
	src_copy = (const unsigned char *)s;
	dest_copy = (unsigned char *)str_pt;
	while (len-- + 1)
		*dest_copy++ = *src_copy++;
	return (str_pt);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	print_lst(void *ptr)
{
	char	*content;

	content = (char *)(ptr);
	if (!content)
		printf("No node to be printed\n");
	printf("%s", content);
}

char	*get_next_line(int fd)
{
	ssize_t				byte_read;
	static t_list		*stash;
	t_list				*node;
	char				*buf;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	*(buf + BUFFER_SIZE) = '\0';
	byte_read = read(fd, buf, BUFFER_SIZE);
	if (byte_read < 0)
	{
		ft_lstclear(&stash, &clear_lst);
		free(buf);
		return ("Error");
	}
	else if (byte_read == 0)
	{
		node = ft_lstnew((void *)(ft_strdup(buf)));
		// wip: something to join all the separate nodes
		ft_lstiter(stash, &print_lst);
	}
	else
	{
		node = ft_lstnew((void *)(ft_strdup(buf)));
		if (ft_strchr(node->content, '\n') != NULL)
		{
			ft_lstadd_back(&stash, node);
			// wip: something to combine,
			// manipulate, and cut list to output [...\n]
			// wip: also freeing lst
		}
		else
			ft_lstadd_back(&stash, node); // newline's should be disappeared
	}
	return ("");
}
