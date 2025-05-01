# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 16:36:50 by dsatge            #+#    #+#              #
#    Updated: 2025/04/29 16:36:51 by dsatge           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

C_FILES = main.c\
			exit.c\
			utils.c\
			philo.c\
			struct.c\
			routine.c\
			survive.c\
			parsing.c\

SRCS = $(addprefix src/,$(C_FILES))

CFLAGS = -Wall -Werror -Wextra -I includes/ -g

all: ${NAME}

$(NAME): $(SRCS)
	@echo "$(BOLD)$(RED)Creation de $(NAME)...$(RESET)"
	@cc $(CFLAGS) $(SRCS) -o $(NAME) $(DEPS) -lreadline
	@echo "$(BOLD)$(YELLOW) COMPILATION TERMINE $(RESET)"

clean:
	@echo "Cleaned"

fclean: clean
	@echo "Removing executable..."
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re