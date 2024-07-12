SRC = ft_printf.c ft_printf_tools.c

HEADER = libft_printf.h

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

all :		$(OBJ)

$(OBJ):		$(SRC)
				cc $(FLAG) -c $(HEADER) $(SRC)

clean :
				rm -f $(OBJ)

fclean : clean

re : fclean all
