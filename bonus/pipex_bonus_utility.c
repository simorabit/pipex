/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:24 by mal-mora          #+#    #+#             */
/*   Updated: 2024/02/13 13:39:14 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	open_file(int is_heredoc, char **arv)
{
	int	fd_in;

	if (is_heredoc == 1)
		fd_in = open("test.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd_in = open(arv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		(perror("Error in open file"), exit(EXIT_FAILURE));
	return (fd_in);
}

void	free_cmd(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
