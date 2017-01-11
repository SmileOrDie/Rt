# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#              #
#    Updated: 2016/12/15 19:55:30 by shamdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= rtv1
CC		= gcc
WFLAGS	= -Wall -Wextra -Werror -g
OPTI	= -I

LS		= ls -1
GREP	= grep
MKDIR	= mkdir -p
RM		= rm -rf

LFLAGS 		= -Llib/ -lft -lmlx
DSRC		= src
DLIB		= libft
DLIBX		= minilibx
DINC		= includes
DINCLIB		= includes \
		  		  $(DLIB)/inc
DINCLIBX	= includes \
		  		  $(DLIBX)/inc
DOBJ	= obj

FSRC		:= $(shell $(LS) $(DSRC) | $(GREP) \.c$)
FOBJ		:= $(FSRC:.c=.o)
LIBFT		:= libft.a
MINILIBX	:= libmlx.a

FSRC		:= $(addprefix $(DSRC)/, $(FSRC))
FOBJ		:= $(addprefix $(DOBJ)/, $(FOBJ))
FINCLIB		:= $(addprefix $(OPTI) , $(DINCLIB))
FINCLIBX	:= $(addprefix $(OPTI) , $(DINCLIBX))
LIBFT		:= $(addprefix $(DLIB)/, $(LIBFT))
MINILIBX	:= $(addprefix $(DLIBX)/, $(MINILIBX))
INC 		= $(addprefix -I,$(DINC))

all: libft minilibx $(FOBJ) $(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(FOBJ)
		$(CC) $(WFLAGS) $(INC) $(FOBJ) $(LIBFT) $(MINILIBX) vector/vector.a -o $@ -framework OpenGL -framework AppKit

$(DOBJ)/%.o: $(DSRC)/%.c $(DINC)
		@$(MKDIR) $(DOBJ)
			$(CC) $(WFLAGS) -c $< $(FINCLIB) $(FINCLIBX) -o $@

libft:
		make -C $(DLIB)
		make -C $(DLIBX)
		make -C vector

clean:
		make -C $(DLIBX) clean
		make -C $(DLIB) clean
		make -C vector clean
			$(RM) $(DOBJ)

fclean: clean
		make -C $(DLIB) fclean
		make -C vector fclean
			$(RM) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
