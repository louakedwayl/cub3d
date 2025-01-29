NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

# dir/file.c
SRCFILES =	main.c \
			ray_casting/raycast.c \
			
SRCDIR = ./srcs/
SRCS = $(addprefix $(SRCDIR), $(SRCFILES))
OBJDIR = ./build/
OBJS = $(addprefix $(OBJDIR), $(notdir $(SRCFILES:.c=.o)))
DEPS = $(OBJS:.o=.d)

HEADERDIR = ./includes/
INCLUDES = -I $(HEADERDIR)

LIBS =  -lreadline

LIBFT_NAME = libft.a
LIBFT_PATH = ./libft/
LIBFT_LIB = $(LIBFT_PATH)$(LIBFT_NAME)
INCLUDES += -I $(LIBFT_PATH)
LIBS += $(LIBFT_LIB)


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

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS) $(MLX_LIB)
	@ echo -n "\r"
	@ echo    "$(GREEN_COLOR)project : compiling c files ... $(TOTAL_FILES)/$(TOTAL_FILES)    ✅$(RESET_COLOR)"
	@ echo -n "$(BLUE_COLOR)- $(NB_COMPILED) files updated -$(RESET_COLOR)\n\n"
	@ echo -n "compiling $(NAME)..."
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(INCLUDES) $(MLX_LIB) $(MLX_FLAGS)
	@ echo -n "\r"
	@ echo "$(GREEN_COLOR)$(NAME) compiled    ✔$(RESET_COLOR)"

$(MLX_LIB):
	@make -C $(MLX_DIR) 

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

clean:
	@ $(MAKE) --no-print-directory cleanself
	@ make clean -s -C $(LIBFT_PATH)
	@ echo "$(PURPLE_COLOR)LIBFT : OBJs cleaned$(RESET_COLOR)"

cleanself:
	@ rm -f $(OBJS) $(DEPS)
	@ echo "$(CYAN_COLOR)project : OBJs cleaned$(RESET_COLOR)"

fclean: cleanself
	@ rm -f $(NAME)
	@ echo "$(CYAN_COLOR)$(NAME) binary cleaned$(RESET_COLOR)"
	@ make fclean -s -C $(LIBFT_PATH)
	@ echo "$(PURPLE_COLOR)LIBFT all cleaned$(RESET_COLOR)"

re: fclean
	@ $(MAKE) --no-print-directory all

-include $(DEPS)

# show a variable value with : make print-VARIABLE
print-%:
	@ echo $* = $($*)

.PHONY: all clean cleanself fclean re
