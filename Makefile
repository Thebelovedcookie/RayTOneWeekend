NAME = minirt

#DIRECTORY
SRC_PATH = src/
OBJ_PATH = obj/
HEADER_FOLDER = includes

SRC = main.c fill_scene.c scene.c init_scene.c \
add_object.c error.c free.c  free_2.c window.c \
render.c render_utils.c math_formule.c math_formule_2.c math_formule_3.c \
hit_plane.c sphere_intersection.c camera.c cylinder.c phong.c shadow.c \
shadow_cy.c cylinder_2.c utils_scene_parse.c fill_scene_2.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ 	= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/

CFLAGS = -Wall -Werror -Wextra -g3
FLAGS = -lXext -lX11 -lm -fPIE 



all : $(NAME)

$(NAME) : $(OBJS)
		@cc $(CFLAGS) $(OBJS) -o $(NAME) libmlx.a libft.a $(FLAGS)
		@echo "$(GREEN) compilation ok $(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@if [ ! -e $(OBJ_PATH) ]; then\
		mkdir -p $(OBJ_PATH);\
		fi
		@$(MAKE) -C ./libft
		@cp ./libft/libft.a .
		@$(MAKE) -C ./minilibx-linux
		@cp ./minilibx-linux/libmlx.a .
		@cc $(CFLAGS) -c $< -o $@ $(INCS)
#$(CC) $(CFLAGS) -c $< -o $@ $(INCS) 


clean : 
		rm -rf $(OBJ_PATH)
		@$(MAKE) -s clean -C ./libft
		@$(MAKE) -s clean -C ./minilibx-linux
		@rm -f libft.a libmlx.a
		@echo "$(CLEAR) $(BLUE) cleaned $(RESET)"

#	@rm -f $(OBJ)
fclean : clean
		@$(MAKE) -s fclean -C ./libft
		@rm -rf $(NAME)
		@echo "$(CLEAR) $(BLUE) cleaned $(RESET)"
		
re : fclean all

.PHONY: all clean fclean re

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[38;5;97m
CLEAR = \033[2J\033[H
RESET = \033[0m