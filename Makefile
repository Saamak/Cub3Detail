# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 17:44:47 by kprigent          #+#    #+#              #
#    Updated: 2024/08/26 15:32:26 by ppitzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = srcs/src/main.c \
		srcs/src/input_verifs.c \
		srcs/src/files_verifs.c \
		srcs/src/data_read.c \
		srcs/src/read_map.c \
		srcs/src/utils.c \
		srcs/src/init_parsing.c \
		srcs/src/print.c \
		srcs/src/utils_two.c \
		srcs/src/free.c \
		srcs/src/error.c \
		srcs/src/rgb_process.c \
		srcs/src/map_data_texture.c \
		srcs/src/map_data_color.c \
		srcs/src/go_render.c \
		srcs/src/go_render_utils.c \
		srcs/src/go_render_init.c \
		srcs/src/ray_casting_2D.c \
		srcs/src/ray_casting_3D.c \
		srcs/src/error_two.c \
		srcs/src/texturize.c \
		srcs/src/close_window.c

OBJTS = $(SRCS:.c=.o)

HEADER = -I includes
CFLAGS = -Wall -Wextra -Werror -g

$(NAME): $(OBJTS)
	@${MAKE} -j -C ./libft -s
	@${MAKE} -j -C ./MacroLibX -s
	cc -o $(NAME) $(OBJTS) ./libft/libft.a ./MacroLibX/libmlx.so -lSDL2 -lm

RM	= rm -f

all:	${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@${MAKE} -j -C ./libft clean -s
	${MAKE} -C ./MacroLibX clean
	${RM} ${OBJTS}

fclean:	clean
	@${MAKE} -j -C ./libft fclean -s
	${MAKE} -C ./MacroLibX fclean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
