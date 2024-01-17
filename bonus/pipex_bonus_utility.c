/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:24 by mal-mora          #+#    #+#             */
/*   Updated: 2024/01/17 11:19:47 by mal-mora         ###   ########.fr       */
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

char *check_env(char *cmd, char **env)
{
    int     i;
    char    *path;
    char    **all_paths;
    char    *result;
    char    *newcmd;
    
    i = 0;
    if (*env == NULL)
        (perror("PATH not found"), exit(EXIT_FAILURE));
    while (env[i])
    {
        path = ft_strnstr(env[i], "PATH", 100);
        if (path)
            break;
        i++;
    }
   
    if (path == NULL)
        (perror("PATH not found"), exit(EXIT_FAILURE));
    all_paths = ft_split(path + 5, ':');
    if (!all_paths)
        return (NULL);
    i = 0;
    
    while (all_paths[i])
    {
        newcmd = ft_strjoin("/", cmd);
        if (!newcmd)
            (free_cmd(all_paths), exit(EXIT_FAILURE));
        result = ft_strjoin(all_paths[i], newcmd);
        if (!result)
            (free_cmd(all_paths), free(newcmd), exit(EXIT_FAILURE));
        if (access(result, F_OK | X_OK) == 0)
            return (free_cmd(all_paths), free(newcmd), result);
        i++;
        free(newcmd);
        free(result);
    }
    return (free_cmd(all_paths), NULL);
}

char **get_command_paths(char *arv[], char **env, int argc)
{
    int i;
    int j;
    int max;
    char **cmds;
    int files;
    char **mcmd;
    
    i = 0;
    if (!ft_strncmp(arv[1], "here_doc", 9))
    {
        j = 3;
        max = 4;
        files = 4;
    }
    else
        (j = 2, max = 3, files = 3);
    cmds = malloc(sizeof(char *) * (argc - max + 1));
    if (!cmds)
        (exit(EXIT_FAILURE));
    while (i < argc - files)
    {
        mcmd = ft_split(arv[j++], ' ');
        if (!mcmd)
            (exit(EXIT_FAILURE));
        cmds[i] = check_env(mcmd[0], env);
        if (cmds[i] == NULL)
            (free_cmd(cmds), free_cmd(mcmd), ft_putstr_fd("command not found", 0), exit(EXIT_FAILURE));
        i++;
    }
    cmds[i] = NULL;
    free_cmd(mcmd);
    return (cmds);
}
