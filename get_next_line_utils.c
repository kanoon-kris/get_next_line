/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 12:24:01 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/05 00:36:36 by kboonkos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
		(*del)(lst->content);
	free(lst);
}

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
