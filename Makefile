# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 17:30:31 by mal-mora          #+#    #+#              #
#    Updated: 2024/02/13 11:49:46 by mal-mora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

BPATH = ./bonus/

SRCS_BONUS	=	bonus/pipex_bonus.c bonus/pipex_bonus_utility.c \
				bonus/ft_split.c \
				bonus/get_command_paths.c \
				bonus/get_next_line/get_next_line.c \
				bonus/get_next_line/get_next_line_utils.c

SRCS		=	pipex.c \
				pipex_utility.c ft_split.c pipex_cmds.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

TARGET = pipex

TARGET_BONUS = pipex_bonus

all: $(TARGET)

bonus: $(TARGET_BONUS)

$(TARGET): $(OBJS) pipex.h
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	
%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@
	
$(TARGET_BONUS): $(OBJS_BONUS) $(BPATH)pipex_bonus.h
	$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS)	

$(BPATH)%.o: $(BPATH)%.c $(BPATH)pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(TARGET) $(TARGET_BONUS)
    
re: fclean all
