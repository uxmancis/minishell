# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 20:29:37 by uxmancis          #+#    #+#              #
#    Updated: 2024/06/19 21:21:15 by dbonilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
INCLUDES	=	inc/
SRC_DIR		=	src/
CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address -g3
AR			=	ar rc
RM			=	rm -f

SRC_FILES =	ft_is/ft_isalpha.c ft_is/ft_isdigit.c ft_is/ft_isalnum.c ft_is/ft_isascii.c ft_is/ft_isprint.c  ft_is/ft_isspace.c\
			ft_mem/ft_calloc.c ft_mem/ft_memset.c ft_mem/ft_bzero.c ft_mem/ft_memcpy.c ft_mem/ft_memmove.c \
			ft_mem/ft_memchr.c ft_mem/ft_memcmp.c \
			ft_put/ft_putchar_fd.c ft_put/ft_putendl_fd.c ft_put/ft_putnbr_fd.c \
			ft_str/ft_striteri.c ft_str/ft_strnstr.c ft_str/ft_strtrim.c ft_str/ft_split.c ft_str/ft_strmapi.c \
			ft_str/ft_strlcpy.c ft_str/ft_strlcat.c ft_str/ft_strchr.c ft_str/ft_strrchr.c ft_str/ft_split_command.c \
			ft_str/ft_strlen.c ft_str/ft_strncmp.c ft_str/ft_strdup.c ft_str/ft_strjoin.c ft_str/ft_substr.c  \
			ft_utils/ft_atoi.c ft_utils/ft_toupper.c ft_utils/ft_tolower.c ft_utils/ft_itoa.c\
			

SRC	=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ	=	$(SRC:.c=.o)

GREEN = \033[0;92m
BLUE = \033[0;94m

# **************************************************************************************** #
all:			$(NAME)

$(NAME):		$(OBJ)
				@$(AR) $(NAME) $(OBJ)
				@echo "$(GREEN)LIBFT COMPILED SUCCESFUL!$(DEF_COLOR)"
.c.o:			
				@echo "$(BLUE)COMPILING... $< $(DEF_COLOR)"
				@$(CC) $(CCFLAGS) -I$(INCLUDES) -c $< -o $(<:.c=.o)
clean:
				@$(RM) $(OBJ)
				@echo "$(YELLOW)FILES REMOVED!$(DEF_COLOR)"

fclean:			clean
				@$(RM) $(NAME)
# @ "$(RED)$(NAME) REMOVED!$(DEF_COLOR)"

re:				fclean all

.PHONY:			all clean fclean re