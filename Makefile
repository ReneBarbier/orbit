NAME = four_line.a
FOUR_LINE = four_line

CC = gcc

CFLAGS = -Wall -Wextra -g

OBJS_DIR = obj
OBJS_SUBS =	$(OBJS_DIR)
SRCS_DIR = srcs

MLX_PATH = mlx/
MLX_LIB = $(MLX_PATH)libmlx.a
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

SOURCES = four_line.c

OBJECTS = $(addprefix $(OBJS_DIR)/,$(SOURCES:.c=.o))

all: subsystems $(NAME) $(FOUR_LINE)

$(NAME) : $(OBJS_SUBS) $(OBJECTS)
	$(AR) -r $(NAME) $(OBJECTS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c inc/four_line.h
	@$(CC) $(CFLAGS) -I mlx -c $< -o $@

$(OBJS_DIR):
	-@mkdir $(OBJS_DIR)

subsystems:
	make -C $(MLX_PATH) all

$(FOUR_LINE) : $(MLX_LIB) $(NAME)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(MLX_LIB) $(NAME) -o $@
	@rm -r $(NAME)

clean :
	@make -C $(MLX_PATH) clean
	@rm -fr $(OBJS_DIR)
	@rm -f $(NAME)

fclean : clean
	@rm -f $(FOUR_LINE)

re: fclean all

.PHONY: all clean fclean re norm
