# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgladush <vgladush@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/15 12:03:00 by vkovsh            #+#    #+#              #
#    Updated: 2018/02/03 16:45:39 by vgladush         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

GC_FLGS = gcc -Wall -Werror -Wextra

SRC_DIR = ./
INC_DIR = ./Includes/ $(LB_PATH)/Includes/
OBJ_DIR = ./obj/
LB_PATH = ./libft/
LB_LINK	= -lmlx -framework OpenGL -framework AppKit -L ./libft -lft

OBJ		= $(addprefix $(OBJ_DIR),$(OBJS))
INC		= $(addprefix -I, $(INC_DIR))

OBJS	= $(SRCS:.c=.o)

SRCS	= ft_fdf.c ft_logfdf.c ft_finfdf.c

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LB_PATH)
	@gcc -o $(NAME) $(OBJ) $(LB_LINK)
	@echo $(NAME) "ready"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(GC_FLGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LB_PATH) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LB_PATH) fclean
	@rm -f $(NAME)
	@echo $(NAME) "deleted"

re: fclean all
