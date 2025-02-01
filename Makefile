# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajosse <ajosse@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 16:11:50 by ajosse            #+#    #+#              #
#    Updated: 2025/02/01 17:20:23 by ajosse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# dir/file.c
SRCFILES =	main.c \
			start_game.c \
			parsing/check_args.c \
			ray_casting/debug.c \
			ray_casting/draw_simple.c \
			ray_casting/free.c \
			ray_casting/hook.c \
			ray_casting/init.c \
			ray_casting/raycast.c \
			ray_casting/utils.c \
			ray_casting/conversion.c \
			ray_casting/conversion2.c \
			ray_casting/draw.c \
			ray_casting/draw_column.c \
			ray_casting/update.c \
			

SRCDIR = ./srcs/
SRCS = $(addprefix $(SRCDIR), $(SRCFILES))
OBJDIR = ./build/
OBJS = $(addprefix $(OBJDIR), $(notdir $(SRCFILES:.c=.o)))
DEPS = $(OBJS:.o=.d)

HEADERDIR = ./includes/
INCLUDES = -I $(HEADERDIR)

LIBFT_NAME = libft.a
LIBFT_PATH = ./libft/
LIBFT_LIB = $(LIBFT_PATH)$(LIBFT_NAME)

MLX_NAME = libmlx.a
MLX_PATH = ./minilibx-linux/
MLX_LIB = $(MLX_PATH)$(MLX_NAME)

INCLUDES += -I $(LIBFT_PATH)
INCLUDES += -I $(MLX_PATH)

LIBS = -L$(MLX_PATH)
LIBS += -lmlx -lX11 -lXext -lm

LIBS += -L$(LIBFT_PATH)
LIBS += -lft

NAME = cub3d

NB_COMPILED = 0
TOTAL_FILES := $(shell echo $(words $(SRCFILES))| bc)

# \033[1;xxm for bold (gras)
RESET_COLOR  = \033[m
BLACK_COLOR  = \033[0;30m
RED_COLOR    = \033[0;31m
GREEN_COLOR  = \033[0;32m
YELLOW_COLOR = \033[0;33m
BLUE_COLOR   = \033[0;34m
PURPLE_COLOR = \033[0;35m
CYAN_COLOR   = \033[0;36m
WHITE_COLOR  = \033[0;37m
ORANGE_COLOR = \033[1;38;5;214m
PINK_COLOR   = \033[1;38;5;13m
BROWN_COLOR  = \033[1;38;5;94m

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	@ echo -n "\r"
	@ echo    "$(GREEN_COLOR)project : compiling c files ... $(TOTAL_FILES)/$(TOTAL_FILES)    ✅$(RESET_COLOR)"
	@ echo -n "$(BLUE_COLOR)- $(NB_COMPILED) files updated -$(RESET_COLOR)\n\n"
	@ echo -n "compiling $(NAME)..."
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@ echo -n "\r"
	@ echo "$(GREEN_COLOR)$(NAME) compiled    ✔$(RESET_COLOR)"

#                        assert it's existing
$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	@ $(CC) $(CFLAGS) $(INCLUDES) -MMD -MF $(@:.o=.d) -c $< -o $@
	@ $(eval NB_COMPILED=$(shell echo $(NB_COMPILED) + 1 | bc))
	@ echo -n "\r"
	@ echo -n "$(CYAN_COLOR)project : compiling c files ... $(NB_COMPILED)/$(TOTAL_FILES)$(RESET_COLOR)"

$(OBJDIR)%.o: $(SRCDIR)*/%.c | $(OBJDIR)
	@ $(CC) $(CFLAGS) $(INCLUDES) -MMD -MF $(@:.o=.d) -c $< -o $@
	@ $(eval NB_COMPILED=$(shell echo $(NB_COMPILED) + 1 | bc))
	@ echo -n "\r"
	@ echo -n "$(CYAN_COLOR)project : compiling c files ... $(NB_COMPILED)/$(TOTAL_FILES)$(RESET_COLOR)"

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

$(LIBFT_LIB):
	@ echo -n "compiling $(LIBFT_NAME)..."
	@ make -s -C $(LIBFT_PATH)
	@ echo -n "\r"
	@ echo "$(GREEN_COLOR)$(LIBFT_NAME) compiled    ✔$(RESET_COLOR)"

$(MLX_LIB):
	@ echo -n "compiling $(MLX_NAME)..."
	@ make -s -C $(MLX_PATH) > mlxlog 2>&1
	@ rm mlxlog
	@ echo -n "\r"
	@ echo "$(GREEN_COLOR)$(MLX_NAME) compiled    ✔$(RESET_COLOR)"

clean:
	@ $(MAKE) --no-print-directory cleanself
	@ make clean -s -C $(LIBFT_PATH)
	@ make clean -s -C $(MLX_PATH) > mlxlog 2>&1
	@ rm mlxlog
	@ echo "$(PURPLE_COLOR)LIBFT : OBJs cleaned$(RESET_COLOR)"

cleanself:
	@ rm -f $(OBJS) $(DEPS)
	@ echo "$(CYAN_COLOR)project : OBJs cleaned$(RESET_COLOR)"

fclean: cleanself
	@ rm -f $(NAME)
	@ echo "$(CYAN_COLOR)$(NAME) binary cleaned$(RESET_COLOR)"
	@ make fclean -s -C $(LIBFT_PATH)
	@ make clean -s -C $(MLX_PATH) > mlxlog 2>&1
	@ rm mlxlog
	@ echo "$(PURPLE_COLOR)LIBFT all cleaned$(RESET_COLOR)"

re: fclean
	@ $(MAKE) --no-print-directory all

-include $(DEPS)

# show a variable value with : make print-VARIABLE
print-%:
	@ echo $* = $($*)

.PHONY: all clean cleanself fclean re
