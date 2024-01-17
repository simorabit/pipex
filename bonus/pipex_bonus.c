/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:27 by mal-mora          #+#    #+#             */
/*   Updated: 2024/01/17 11:55:39 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void free_cmd(char **cmds)
{
    int i;
    
    i = 0;
    while (cmds[i] != NULL)
    {
        free(cmds[i]);
        i++;
    }
    free(cmds);
}

static void execute(char *path, char *cmd)
{
    char **s_cmd = NULL;
    s_cmd = ft_split(cmd, ' ');
    if (!s_cmd)
        (free(cmd), exit(EXIT_FAILURE));
    if (execve(path, s_cmd, NULL) == -1)
    {
        free_cmd(s_cmd);
        free(cmd);
        perror("Error in execve for command2");
        exit(EXIT_FAILURE);
    }
}

static void  write_in_file2(char *cmd, char *arv[], int argc, int x)
{
    int fd_out;
    int fds;
    fds = fork();
    if (!fds)
    {
        if (x == 1)
            fd_out = open(arv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd_out = open(arv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
            (perror("Error in open file"), exit(EXIT_FAILURE));
        if (dup2(fd_out, 1) == -1)
            (perror("Error in dup2"), exit(EXIT_FAILURE));
        close(fd_out);
        execute(cmd, arv[argc - 2]);
    }
}

static void manage_pipe(char *path, char *cmd)
{
    int pid;
    int p_fd[2];

    if (pipe(p_fd) == -1)
        (free(cmd), perror("pipe"), exit(EXIT_FAILURE));
    pid = fork();
    if (pid == -1)
        free(cmd), exit(EXIT_FAILURE);
    if (!pid)
    {
        close(p_fd[0]);
        if (dup2(p_fd[1], STDOUT_FILENO) == -1)
            (free(cmd), perror("Error in dup2"), exit(EXIT_FAILURE));
        close(p_fd[1]);
        execute(path, cmd);
    }
    close(p_fd[1]);
    if (dup2(p_fd[0], STDIN_FILENO) == -1)
        (free(cmd), perror("Error in dup2"), exit(EXIT_FAILURE));
    close(p_fd[0]);
}

static int handel_here_doc(char *arv[])
{
    int fd_in;
    char *line;
    int i;
    int j;

    i = 3;
    j = 0;
    fd_in = open("file_test.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd_in == -1)
        (perror("Error in open file"), exit(EXIT_FAILURE));
    line = get_next_line(0);
    char *limiter = ft_strjoin(arv[2], "\n");
    while (ft_strncmp(line, limiter, ft_strlen(limiter)))
    {
        ft_putstr_fd(line, fd_in);
        free(line);
        line = get_next_line(0);
    }
    (free(limiter), free(line), close(fd_in));
    return (1);
}

// unlink the file created in the here_doc

int open_file(int is_heredoc, char **arv)
{
    int fd_in;
    if (is_heredoc == 1)
        fd_in = open("file_test.txt", O_CREAT | O_RDWR | O_APPEND , 0644);
    else
        fd_in = open(arv[1], O_RDONLY, 0777);
    if (fd_in == -1)
        (perror("Error in open file"), exit(EXIT_FAILURE));
    return fd_in;
}

void    f()
{
    system("leaks pipex_bonus");
}

int main(int argc, char *arv[], char **env)
{
    int fd_in;
    int i;
    int j;

    atexit(f);
    char **cmds;
    int is_heredoc;
    (void)env;
    is_heredoc = 0;
    if (argc < 5)
        (ft_putstr_fd("argument required is 4", 0), exit(EXIT_FAILURE));
    if (!ft_strncmp(arv[1], "here_doc", 9))
        is_heredoc = handel_here_doc(arv);
    i = 2 + is_heredoc;
    j = 0;
    cmds = get_command_paths(arv, env, argc);
    fd_in = open_file(is_heredoc, arv);
    if (dup2(fd_in, STDIN_FILENO) == -1)
        perror("INFILE ERROR");
    close(fd_in);
    while (i < argc - 2)
        manage_pipe(cmds[j++], arv[i++]);
    if (i == argc - 2)
        write_in_file2(cmds[j], arv, argc, is_heredoc);
    free_cmd(cmds);
    i = -1;
    close(STDIN_FILENO);
    while (++i < argc - 3)
        wait(NULL);
}
