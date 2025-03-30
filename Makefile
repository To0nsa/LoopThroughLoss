# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 18:23:28 by nlouis            #+#    #+#              #
#    Updated: 2025/03/30 16:17:21 by nlouis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I libft/include -I ./include -I raylib/src -g -fsanitize=address -fsanitize=undefined

NAME = LoopThroughLoss

SRCS := $(shell find srcs -name "*.c")
OBJSDIR = objs
OBJS   = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

LIBFT   = libft/lib/libft.a

# LDFLAGS Raylib pour Linux
LDFLAGS = -Llibft/lib -lft -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Pour macOS :
# LDFLAGS = -Llibft/lib -lft -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	make -C libft

$(OBJSDIR)/%.o: %.c include/LoopThroughLoss.h
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
