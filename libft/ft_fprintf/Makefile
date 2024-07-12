SRC = ft_fprintf.c ft_fprintf_tools.c

HEADER = libft_fprintf.h

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

all :		$(OBJ)

$(OBJ):		$(SRC)
				cc $(FLAG) -c $(HEADER) $(SRC)

clean :
				rm -f $(OBJ)

fclean : clean

re : fclean all

