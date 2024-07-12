# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 09:24:12 by mmahfoud          #+#    #+#              #
#    Updated: 2024/06/19 17:30:04 by mmahfoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
CFLAGS			= -Werror -Wall -Wextra

SRC				= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
				ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
				ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
				ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
				ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
				ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_atoi_base.c ft_strncpy.c ft_strscpy.c ft_atol.c \
				ft_strtod.c

SRC_PRINTF		= ./ft_printf/ft_printf.c ./ft_printf/ft_printf_tools.c

SRC_FPRINTF		= ./ft_fprintf/ft_fprintf.c ./ft_fprintf/ft_fprintf_tools.c

SRC_GNL			= ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

HEADER_PRINTF	= ./ft_printf/libft_printf.h

HEADER_FPRINTF  = ./ft_fprintf/libft_fprintf.h

HEADER_GNL		= ./get_next_line/get_next_line.h

OBJ				= $(SRC:.c=.o)

OBJ_PF			= $(SRC_PRINTF:.c=.o)

OBJ_FPF         = $(SRC_FPRINTF:.c=.o)

OBJ_GNL			= get_next_line.o get_next_line_utils.o

HEADER			= libft.h

all:			$(NAME) 

$(NAME):		$(OBJ) $(OBJ_PF) $(OBJ_FPF) $(OBJ_GNL)
					@ar rcs $(NAME) $(OBJ) $(OBJ_PF) $(OBJ_GNL) $(OBJ_FPF)
					@ranlib $(NAME)
					@echo "done."

$(OBJ):			$(SRC) 
					@cc $(CFLAGS) -c $(HEADER) $(SRC)

$(OBJ_GNL):		$(SRC_GNL)
					@cc $(CFLAGS) -c $(HEADER_GNL) $(SRC_GNL)

$(OBJ_PF) :		$(SRC_PRINTF)
					$(MAKE) -C ./ft_printf

$(OBJ_FPF) :	$(SRC_FPRINTF)
					$(MAKE) -C ./ft_fprintf
clean:
					@rm -f $(OBJ) $(OBJ_PF) $(OBJ_FPF)
					@rm -f $(OBJ_GNL)
					@echo "clean done."

fclean:			clean
					@rm -f $(NAME)

re:				fclean all
