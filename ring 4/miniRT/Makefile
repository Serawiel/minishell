NAME = miniRT

SRCS = mandatory/srcs/parsing/parsing_master.c \
       mandatory/srcs/parsing/parsing_ambient.c \
       mandatory/srcs/parsing/parsing_objects.c \
       mandatory/srcs/parsing/parsing_calcul.c \
	   mandatory/srcs/parsing/verify_ambient.c \
	   mandatory/srcs/parsing/verify_camera.c \
	   mandatory/srcs/parsing/verify_cylinder.c \
	   mandatory/srcs/parsing/verify_light.c \
	   mandatory/srcs/parsing/verify_plane.c \
	   mandatory/srcs/parsing/verify_sphere.c \
       mandatory/srcs/graphics/init.c \
       mandatory/srcs/graphics/hooks.c \
       mandatory/srcs/graphics/ray.c \
       mandatory/srcs/graphics/color.c \
       mandatory/srcs/graphics/hit.c \
       mandatory/srcs/graphics/hit_sphere.c \
       mandatory/srcs/graphics/hit_plane.c \
       mandatory/srcs/graphics/hit_cylinder.c \
       mandatory/srcs/graphics/light.c \
       mandatory/srcs/graphics/objects/sphere.c \
       mandatory/srcs/graphics/objects/planes.c \
       mandatory/srcs/graphics/objects/cylinder.c \
       mandatory/srcs/graphics/objects/cylinder2.c \
       mandatory/srcs/utils/free.c \
       mandatory/srcs/utils/error.c \
       mandatory/srcs/utils/utils.c \
       mandatory/srcs/utils/op_vector.c \
       mandatory/srcs/utils/op_vec_two.c \
       mandatory/srcs/main.c

SRCS_BONUS = bonus/srcs/parsing/parsing_master.c \
       bonus/srcs/parsing/parsing_ambient.c \
       bonus/srcs/parsing/parsing_objects.c \
       bonus/srcs/parsing/parsing_calcul.c \
	bonus/srcs/parsing/verify_ambient.c \
	bonus/srcs/parsing/verify_camera.c \
	bonus/srcs/parsing/verify_cylinder.c \
	bonus/srcs/parsing/verify_light.c \
	bonus/srcs/parsing/verify_plane.c \
	bonus/srcs/parsing/verify_sphere.c \
       bonus/srcs/graphics/init.c \
       bonus/srcs/graphics/hooks.c \
       bonus/srcs/graphics/ray.c \
       bonus/srcs/graphics/color.c \
       bonus/srcs/graphics/hit.c \
       bonus/srcs/graphics/hit_sphere.c \
       bonus/srcs/graphics/hit_plane.c \
       bonus/srcs/graphics/hit_cylinder.c \
       bonus/srcs/graphics/light.c \
       bonus/srcs/graphics/objects/sphere.c \
       bonus/srcs/graphics/objects/planes.c \
       bonus/srcs/graphics/objects/cylinder.c \
       bonus/srcs/graphics/objects/cylinder2.c \
       bonus/srcs/utils/free.c \
       bonus/srcs/utils/error.c \
       bonus/srcs/utils/utils.c \
       bonus/srcs/utils/op_vector.c \
       bonus/srcs/utils/op_vec_two.c \
       bonus/srcs/main.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Imandatory/includes -I./libft -I./minilibx-linux
INCLUDES_BONUS = -Ibonus/includes -I./libft -I./minilibx-linux

LDFLAGS = -lm -lX11 -lXext

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

GREEN = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
RESET = \033[0m
BOLD = \033[1m

.SILENT:

all: $(LIBFT) $(MLX) $(NAME)
	echo "$(GREEN)✓ miniRT ready! 🚀$(RESET)"

$(LIBFT):
	make -C libft --no-print-directory

$(MLX):
	make -C minilibx-linux --no-print-directory

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

start:
	wget https://cdn.intra.42.fr/document/document/40722/minilibx-linux.tgz
	tar -xvf minilibx-linux.tgz && rm -rf minilibx-linux.tgz
	@cd minilibx-linux && make
	@cd libft && make && make clean

bonus: INCLUDES=$(INCLUDES_BONUS)
bonus: $(LIBFT) $(MLX) $(OBJS_BONUS)
	echo "$(CYAN)🔗 Linking bonus...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)
	echo "$(GREEN)✓ miniRT bonus ready! ✨$(RESET)"

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	make -C libft clean --no-print-directory

fclean: clean
	@rm -f $(NAME)
	make -C libft fclean --no-print-directory

superclean: fclean
		make -C libft fclean --no-print-directory
		@rm -rf minilibx-linux

re: fclean all

.PHONY: all clean fclean re bonus