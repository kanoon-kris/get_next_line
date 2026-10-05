/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 21:26:49 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/05 00:37:02 by kboonkos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_lstdelone(t_list *lst, void (*del)(void*));

char	*get_next_line(int fd);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	ft_lstclear(t_list **lst, void (*del)(void*));

char	*ft_strchr(const char *s, int c);

void	ft_lstiter(t_list *lst, void (*f)(void *));

size_t	ft_strlen(const char *s);

void	ft_lstadd_back(t_list **lst, t_list *new);

char	*ft_strdup(const char *s);

t_list	*ft_lstnew(void *content);

void	print_lst(void *ptr);

#endif
