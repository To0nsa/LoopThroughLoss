# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 18:23:28 by nlouis            #+#    #+#              #
#    Updated: 2025/03/27 08:56:18 by nlouis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I libft/include -I ./include -I mlx/ -I raylib/src # -g -fsanitize=address -fsanitize=undefined

NAME = LoopingThroughLoss

SRCS := $(shell find srcs -name "*.c")

# SRCS_BONUS =	

OBJSDIR = objs
OBJS   = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

LIBFT   = libft/lib/libft.a
LDFLAGS = -Llibft/lib -lft -Lmlx -lmlx -lXext -lX11 -lm -ldl -lpthread -lGL -lrt -lX11 -lXrandr -lXinerama -lXcursor -lasound -lXi

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	make -C libft

$(OBJSDIR)/%.o: %.c include/cub3d.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJSDIR)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
