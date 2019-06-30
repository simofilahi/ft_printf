# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/27 09:52:01 by mfilahi           #+#    #+#              #
#    Updated: 2019/06/27 10:08:56 by mfilahi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf

OBJS_DIR = objs
LIB = libft/libft.a
SRCS_DIR = srcs
INCS_LIBFT = -I libft/
INCS = -I includes/ $(INCS_LIBFT)
CC = gcc 
Cf_flag = -Wextra -Werror -Wall

SRCS = $(SRCS_DIR)/ft_printf.c \
	   $(SRCS_DIR)/conversions.c \
	   $(SRCS_DIR)/conversions_1.c \
	   $(SRCS_DIR)/bases.c \
	    $(SRCS_DIR)/common_func.c \
	   $(SRCS_DIR)/get_propties.c 

OBJECTS = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJECTS)
		@make -C libft/
		@$(CC) $(OBJECTS) $(LIB) -o $(NAME)

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@$(CC) $(Cf_flag) $(INCS) -c $< -o $@

clean:
	@make -C libft/ clean
	@rm -rf $(OBJS_DIR)

fclean : clean
	@make -C libft/ fclean
	@rm -rf $(NAME)

help :
	@echo "SRCS: $(SRCS)"
	@echo "OBJS_DIR: $(OBJS_DIR)"

re : fclean all