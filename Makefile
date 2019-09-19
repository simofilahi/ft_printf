# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/27 09:52:01 by mfilahi           #+#    #+#              #
#    Updated: 2019/07/01 18:30:34 by mfilahi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

OBJS_DIR = objs
LIB = libft/libft.a
SRCS_DIR = srcs
INCS_LIBFT = -I libft/
INCS = -I includes/ $(INCS_LIBFT)
CC = gcc 
C_FLAG = -Wextra -Werror -Wall

SRCS = $(SRCS_DIR)/ft_printf.c \
	   $(SRCS_DIR)/diouxX_conv.c \
	   $(SRCS_DIR)/cspb_conv.c \
	   $(SRCS_DIR)/bases.c \
	   $(SRCS_DIR)/parser.c \
	   $(SRCS_DIR)/common_func.c \
	   $(SRCS_DIR)/flags.c \
	   $(SRCS_DIR)/float.c \
	   $(SRCS_DIR)/float_op.c \
	   $(SRCS_DIR)/get_propties.c

OBJECTS = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJECTS)
		@make -C libft/
		@ar rc $(NAME) $(OBJECTS) libft/*

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@$(CC) $(C_FLAG) $(INCS) -c $< -o $@

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
