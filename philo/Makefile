# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmaes <rmaes@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/13 15:25:40 by rmaes         #+#    #+#                  #
#    Updated: 2023/05/26 12:51:38 by rmaes         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#Colors

DEFAULT = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m

SOURCES_DIR = sources/
FILES =	philosophers.c philosophers_utils.c ft_atoi.c parsing.c loop_conditions.c isint.c reaper.c thread.c
SOURCES = $(addprefix $(SOURCES_DIR), $(FILES))

OBJECTS_DIR = objects/
OBJECTS = $(addprefix $(OBJECTS_DIR), $(FILES:.c=.o))

CDL_LIST = cdl_list/cdl_list.a

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread 
CC = gcc
NAME = philo

all: $(NAME)

$(NAME): $(OBJECTS) $(CDL_LIST)
	@echo "compiling: $(YELLOW)creating executable$(DEFAULT)"
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo "$(GREEN)$@ successfully compiled!$(DEFAULT)"

$(CDL_LIST):
	@make -C cdl_list

$(OBJECTS_DIR):
	mkdir objects

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(@D)
	@echo "compiling: $(YELLOW)$@$(DEFAULT)"
	@$(CC) -c $(CFLAGS) -o $@ $^

clean:
	@echo "cleaning:  $(RED)removing object files$(DEFAULT)"
	@make clean -C cdl_list
	@rm -f $(OBJECTS)

fclean: clean
	@echo "cleaning:  $(RED)removing $(NAME)$(DEFAULT)"
	@make rmlib -C cdl_list
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re