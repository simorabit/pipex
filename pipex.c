/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:01 by mal-mora          #+#    #+#             */
/*   Updated: 2024/02/12 18:01:32 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_first_command(char *path, int *pip_fd, char *file1, char *cmd1)
{
	int		fd_file1;
	char	**args;

	close(pip_fd[0]);
	fd_file1 = open(file1, O_RDONLY);
	if (fd_file1 == -1)
		(perror("error in file1"), exit(EXIT_FAILURE));
	if (dup2(fd_file1, STDIN_FILENO) == -1)
		(perror("Error in dup2"), exit(EXIT_FAILURE));
	if (dup2(pip_fd[1], STDOUT_FILENO) == -1)
		(perror("Error in dup2"), exit(EXIT_FAILURE));
	(close(fd_file1), close(pip_fd[1]));
	args = ft_split(cmd1, ' ');
	if (execve(path, args, NULL) == -1)
	{
		perror("Error in execve");
		free_cmd(args);
		exit(EXIT_FAILURE);
	}
	free_cmd(args);
}

void	process_second_command(char *path, int *pip_fd, char *cmd2, char *file2)
{
	int		fd_file2;
	char	**args;

	close(pip_fd[1]);
	fd_file2 = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_file2 == -1)
		(perror(file2), exit(EXIT_FAILURE));
	if (dup2(pip_fd[0], STDIN_FILENO) == -1)
		(perror("Error in dup2"), exit(EXIT_FAILURE));
	if (dup2(fd_file2, STDOUT_FILENO) == -1)
		(perror("Error in dup2"), exit(EXIT_FAILURE));
	(close(fd_file2), close(pip_fd[0]));
	args = ft_split(cmd2, ' ');
	if (execve(path, args, NULL) == -1)
	{
		perror("Error in execve for command2");
		free_cmd(args);
		exit(EXIT_FAILURE);
	}
	free_cmd(args);
}

char	*check_env(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*result;
	char	*newcmd;

	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i++], "PATH", 89);
		if (path)
			break ;
	}
	all_paths = ft_split(path + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		newcmd = ft_strjoin("/", cmd);
		result = ft_strjoin(all_paths[i++], newcmd);
		if (access(result, X_OK) == 0)
			return (free_cmd(all_paths), free(newcmd), result);
		(free(newcmd), free(result));
	}
	return (free_cmd(all_paths), NULL);
}

void	process_pipes(char *cmd1, char *cmd2, char **arv)
{
	int	pid;
	int	pip_fd[2];

	if (pipe(pip_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		process_first_command(cmd1, pip_fd, arv[1], arv[2]);
	else
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (!pid)
			process_second_command(cmd2, pip_fd, arv[3], arv[4]);
	}
	(close(pip_fd[0]), close(pip_fd[1]));
}

int	main(int argc, char *arv[], char **env)
{
	char	**path1;
	char	**path2;
	char	*cmd1;
	char	*cmd2;

	if (argc != 5)
		(ft_putstr_fd("argument required is 4", 0), exit(EXIT_FAILURE));
	if (!*env)
		(perror("Error in env"), exit(EXIT_FAILURE));
	path1 = ft_split(arv[2], ' ');
	path2 = ft_split(arv[3], ' ');
	if (!path1 || !path2)
		(ft_putstr_fd("path not found", 0), exit(EXIT_FAILURE));
	cmd1 = get_cmd(path1, env);
	cmd2 = get_cmd(path2, env);
	if (!cmd1 || !cmd2)
		(ft_putstr_fd("path not found", 0), exit(EXIT_FAILURE));
	process_pipes(cmd1, cmd2, arv);
	(wait(NULL), wait(NULL));
	(free_cmd(path1), free_cmd(path2));
	return (1);
}
