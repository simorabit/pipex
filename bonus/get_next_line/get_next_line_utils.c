/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:00:29 by mal-mora          #+#    #+#             */
/*   Updated: 2024/02/04 17:20:24 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src != '\0')
	{
		*ptr = *src;
		src++;
		ptr++;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	while (s && *s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*new_value;

	i = 0;
	new_value = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!new_value)
		return (NULL);
	while (s1[i])
	{
		new_value[i] = s1[i];
		i++;
	}
	new_value[i] = '\0';
	return (new_value);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*result;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == NULL)
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	ptr = ft_strcpy(result, s1);
	ptr = ft_strcpy(result + s1_len, s2);
	*(ptr + s2_len) = '\0';
	return (result);
}
