# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#              #
#    Updated: 2017/08/07 14:47:19 by shamdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= rt
CC		= gcc
WFLAGS	= -Wall -Wextra -Werror -g -o3
OPTI	= -I

LS		= ls -1
GREP	= grep
MKDIR	= mkdir -p
RM		= rm -rf

DSRC		= src
DLIB		= libft
DVECT		= vector
DLIB2		= SDL2/lib
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
VECTOR		:= vector.a
LIBSDL2		:= libSDL2.a
MINILIBX	:= libmlx.a

FSRC		:= $(addprefix $(DSRC)/, $(FSRC))
FOBJ		:= $(addprefix $(DOBJ)/, $(FOBJ))
FINCLIB		:= $(addprefix $(OPTI) , $(DINCLIB))
FINCLIBX	:= $(addprefix $(OPTI) , $(DINCLIBX))
LIBFT		:= $(addprefix $(DLIB)/, $(LIBFT))
VECTOR		:= $(addprefix $(DVECT)/, $(VECTOR))
LIBSDL2		:= $(addprefix $(DLIB2)/, $(LIBSDL2))
MINILIBX	:= $(addprefix $(DLIBX)/, $(MINILIBX))
INC 		= $(addprefix -I,$(DINC))
# minilibx 
all: libft $(FOBJ) $(NAME)
 # $(MINILIBX)
$(NAME): $(LIBFT) $(FOBJ)
		$(CC) $(WFLAGS) $(INC) $(FOBJ) $(LIBFT) $(MINILIBX) $(VECTOR) $(LIBSDL2) -o $@ -framework OpenGL -framework AppKit -framework OpenCL

$(DOBJ)/%.o: $(DSRC)/%.c $(DINC)
		@$(MKDIR) $(DOBJ)
			$(CC) $(WFLAGS) -c $< $(FINCLIB) $(FINCLIBX) -o $@

libsdl2:
		unzip ./SDL2-2.0.5.zip;
		mkdir SDL2
		cd ./SDL2 && ../SDL2-2.0.5/configure --prefix=`pwd`
		make -j8 -C SDL2
		make -C SDL2 install
		rm -rf SDL2-2.0.5

libft:
		if [ -f $(LIBSDL2) ] ; then echo "Nothing to be done" ; else make libsdl2 ; fi
		make -C $(DLIB)
		make -C $(DLIBX)
		make -C $(DVECT)

clean:
		make -C $(DLIBX) clean
		make -C $(DLIB) clean
		make -C $(DVECT) clean
			$(RM) $(DOBJ)

fclean: clean
		make -C $(DLIB) fclean
		make -C $(DVECT) fclean
		rm -rf SDL2
			$(RM) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
