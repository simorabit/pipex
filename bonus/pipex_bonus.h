/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:33 by mal-mora          #+#    #+#             */
/*   Updated: 2024/02/04 17:16:01 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>
# include "get_next_line/get_next_line.h"

char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*check_env(char *cmd, char **env);
char	**get_command_paths(char *arv[], char **env, int argc);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
void	ft_putstr_fd(char *str, int fd);
void	free_cmd(char **cmds);
int		open_file(int is_heredoc, char **arv);

#endif
