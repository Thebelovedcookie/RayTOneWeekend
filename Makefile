NAME = minirt

SRC = main.c fill_scene.c scene.c init_scene.c add_object.c error.c free.c test_function.c window.c render.c math_formule.c hit_plane.c sphere_intersection.c camera.c cylinder.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g3

FLAGS = -lXext -lX11 -lm -fPIE 

all : $(NAME)

$(NAME) : $(OBJ)
		@cc $(CFLAGS) $(OBJ) -o $(NAME) libmlx.a libft.a $(FLAGS)

$(OBJ) : $(SRC)
		@$(MAKE) -C ./libft
		@cp ./libft/libft.a .
		@$(MAKE) -C ./minilibx-linux
		@cp ./minilibx-linux/libmlx.a .
		@cc $(CFLAGS) -c $(SRC)

clean : 
		@$(MAKE) -s clean -C ./libft
		@$(MAKE) -s clean -C ./minilibx-linux
		@rm -f $(OBJ)
		@rm -f libft.a libmlx.a

fclean : clean
		@$(MAKE) -s fclean -C ./libft
		@rm -f $(NAME)
		
re : fclean all
