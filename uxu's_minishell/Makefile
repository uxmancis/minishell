# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 11:09:00 by uxmancis          #+#    #+#              #
#    Updated: 2024/04/14 11:10:52 by uxmancis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Source files and object files
SRC = analyse_input.c minishell.c utils.c
OBJ = $(SRC:.c=.o)

# Executable name
NAME = minishell

# Make all rule
all: $(NAME)

# Build the executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJ)

# Clean everything, including the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re