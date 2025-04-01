# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 18:23:28 by nlouis            #+#    #+#              #
#    Updated: 2025/04/01 23:50:57 by nlouis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g # -fsanitize=address -fsanitize=undefined
NAME     = LoopThroughLoss

# Directories
SRCS_DIR    = srcs
OBJS_DIR    = objs
INCLUDE_DIR = include

# Libft
LIBFT_DIR   = libft
LIBFT_INC   = $(LIBFT_DIR)/include
LIBFT_LIB   = $(LIBFT_DIR)/lib/libft.a

# Raylib
RAYLIB_DIR  = raylib
RAYLIB_SRC  = $(RAYLIB_DIR)/src
RAYLIB_INC  = $(RAYLIB_SRC)
RAYLIB_LIB  = $(RAYLIB_SRC)/libraylib.a

# Includes
PROJ_INC    = $(INCLUDE_DIR)
INCLUDES    = -I$(LIBFT_INC) -I$(PROJ_INC) -I$(RAYLIB_INC)
CFLAGS     += $(INCLUDES)

# Sources and Objects
SRCS    := $(shell find $(SRCS_DIR) -name "*.c")
OBJS    := $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS    := $(OBJS:.o=.d)

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LDFLAGS = -L$(LIBFT_DIR)/lib -lft \
			  -L$(RAYLIB_SRC) -lraylib \
			  -lGL -lm -lpthread -ldl -lrt -lX11
endif

ifeq ($(UNAME_S),Darwin)  # macOS
	LDFLAGS = -L$(LIBFT_DIR)/lib -lft \
			  -L$(RAYLIB_SRC) -lraylib \
			  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

# Targets

all: check-deps $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(RAYLIB_LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT_LIB) $(LDFLAGS)

# Compile object files
$(OBJS_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

# Build libft
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

# Build raylib
$(RAYLIB_LIB):
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP

# Clean
clean:
	rm -f $(OBJS) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(RAYLIB_SRC) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)
	rm -f $(RAYLIB_LIB)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Check for dependencies automatically
check-deps:
ifeq ($(UNAME_S),Linux)
	@echo "🔍 Checking for required development libraries (Linux)..."
	@dpkg -s libgl1-mesa-dev > /dev/null 2>&1 || (echo "⛔ Missing dependencies. Run 'make setup' to install."; exit 1)
endif

ifeq ($(UNAME_S),Darwin)
	@echo "🔍 Checking for Raylib and pkg-config (macOS)..."
	@pkg-config --exists raylib || (echo "⛔ Missing Raylib/pkg-config. Run 'make setup' to install."; exit 1)
endif

# Install Dependencies Based on OS
setup:
ifeq ($(UNAME_S),Linux)
	@echo "🛠 Installing dependencies for Linux..."
	sudo apt update && sudo apt install -y \
		libgl1-mesa-dev \
		libx11-dev \
		libxcursor-dev \
		libxrandr-dev \
		libxi-dev \
		libasound2-dev \
		libpulse-dev \
		libopenal-dev \
		libudev-dev \
		libdrm-dev \
		libgbm-dev \
		libxinerama-dev \
		libxkbcommon-dev \
		alsa-utils \
		build-essential \
		cmake \
		pkg-config
endif

ifeq ($(UNAME_S),Darwin)
	@echo "🛠 Installing dependencies for macOS..."
	brew update
	brew install raylib pkg-config cmake
endif

.PHONY: all clean fclean re setup check-deps
