/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:02:01 by edavid            #+#    #+#             */
/*   Updated: 2021/07/12 18:05:34 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <stdlib.h>
# include <limits.h>
# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif
# define BUFFER_SIZE 100

int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
int		contains_newline(char *str, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strjoin_v3(char **s1, char **s2);
char	*ft_strdup_v2(const char *s, int n);

#endif
