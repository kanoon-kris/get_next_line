/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboonkos <kboonkos@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 21:26:49 by kboonkos          #+#    #+#             */
/*   Updated: 2026/10/09 15:14:05 by kboonkos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);

char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		lst_append(t_list **lst, char *content);
void	lst_clear(t_list **lst);

#endif
