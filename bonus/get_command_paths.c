/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:24 by mal-mora          #+#    #+#             */
/*   Updated: 2024/02/04 17:14:27 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	if (*env == NULL)
		(perror("PATH not found"), exit(EXIT_FAILURE));
	while (env[i++])
	{
		path = ft_strnstr(env[i], "PATH", 100);
		if (path)
			return (path);
	}
	return (NULL);
}

char	*check_all_path(char *path, char *cmd)
{
	char	*result;
	char	*newcmd;

	newcmd = ft_strjoin("/", cmd);
	result = ft_strjoin(path, newcmd);
	if (access(result, F_OK | X_OK) == 0)
		return ((free(newcmd), result));
	(free(newcmd), free(result));
	return (NULL);
}

char	*check_env(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*result;

	i = 0;
	if (*env == NULL || cmd == NULL)
		(perror("PATH not found"), exit(EXIT_FAILURE));
	path = get_path(env);
	if (!path)
		(perror("PATH not found"), exit(EXIT_FAILURE));
	all_paths = ft_split(path + 5, ':');
	if (!all_paths)
		return (NULL);
	while (all_paths[i++])
	{
		result = check_all_path(all_paths[i], cmd);
		if (result)
			return (free_cmd(all_paths), result);
		free(result);
	}
	return (free_cmd(all_paths), NULL);
}

char	**get_command_paths(char *arv[], char **env, int argc)
{
	int		i;
	int		j;
	char	**cmds;
	char	**mcmd;

	i = -1;
	if (!ft_strncmp(arv[1], "here_doc", 9))
		j = 3;
	else
		j = 2;
	cmds = malloc(sizeof(char *) * (argc - j + 2));
	if (!cmds)
		(exit(EXIT_FAILURE));
	while (++i < argc - j + 1)
	{
		mcmd = ft_split(arv[j++], ' ');
		if (!mcmd)
			(free(cmds), exit(EXIT_FAILURE));
		cmds[i] = check_env(mcmd[0], env);
		if (cmds[i] == NULL)
			(ft_putstr_fd("command not found", 0), free_cmd(cmds), \
			free_cmd(mcmd), exit(0));
		free_cmd(mcmd);
	}
	return (cmds[i] = NULL, cmds);
}
