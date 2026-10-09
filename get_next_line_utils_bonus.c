/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 12:24:01 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/09 15:14:38 by kboonkos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

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

int	lst_append(t_list **lst, char *content)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if ((!new_node) || (!content))
		return (free(new_node), free(content), 0);
	new_node->content = content;
	new_node->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_node;
		return (1);
	}
	last_node = *lst;
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = new_node;
	return (1);
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

void	lst_clear(t_list **lst)
{
	t_list	*next_node;

	while (*lst)
	{
		next_node = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = next_node;
	}
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
