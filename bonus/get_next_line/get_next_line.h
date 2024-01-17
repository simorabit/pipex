/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:00:36 by mal-mora          #+#    #+#             */
/*   Updated: 2024/01/11 19:36:29 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../get_next_line/get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(char *s, int c);
size_t  ft_strlen(const char *s);
char	*get_next_line(int fd);

#endif
