/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:29:52 by mal-mora          #+#    #+#             */
/*   Updated: 2024/02/04 16:13:17 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == NULL)
		return (NULL);
	ptr = ft_strcpy(result, s1);
	ptr = ft_strcpy(result + s1_len, s2);
	*(ptr + s2_len) = '\0';
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((n > i) && (s1[i] == s2[i]) && (s1[i] != '\0'))
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_size;

	if (!needle[0] || haystack == needle)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	needle_size = ft_strlen(needle);
	while (*haystack && i < len && (i + needle_size <= len))
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp((char *)haystack, (char *)needle, needle_size) == 0)
				return ((char *)(haystack));
		}
		i++;
		haystack++;
	}
	return (NULL);
}
