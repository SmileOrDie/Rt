# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/15 19:28:38 by shamdani          #+#    #+#              #
#    Updated: 2017/08/09 17:09:39 by magouin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= rt
CC		= gcc
WFLAGS	= -Wall -Wextra -Werror -g -o3 -I./SDL2/include/SDL2
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
LIBSDL2_IMG := libSDL2_image.dylib
MINILIBX	:= libmlx.a

FSRC		:= $(addprefix $(DSRC)/, $(FSRC))
FOBJ		:= $(addprefix $(DOBJ)/, $(FOBJ))
FINCLIB		:= $(addprefix $(OPTI) , $(DINCLIB))
FINCLIBX	:= $(addprefix $(OPTI) , $(DINCLIBX))
LIBFT		:= $(addprefix $(DLIB)/, $(LIBFT))
VECTOR		:= $(addprefix $(DVECT)/, $(VECTOR))
LIBSDL2		:= $(addprefix $(DLIB2)/, $(LIBSDL2))
LIBSDL2_IMG	:= $(addprefix $(DLIB2)/, $(LIBSDL2_IMG))
MINILIBX	:= $(addprefix $(DLIBX)/, $(MINILIBX))
INC 		= $(addprefix -I,$(DINC))

all: libft $(FOBJ) $(NAME)

$(NAME): $(LIBFT) $(FOBJ)
		$(CC) $(WFLAGS) $(INC) $(LIBSDL2_IMG) $(FOBJ) $(LIBFT) $(MINILIBX) $(VECTOR) -o $@ -framework OpenGL -framework AppKit -framework OpenCL -L./SDL2/lib ./SDL2/.libs/libSDL2_image.dylib ./SDL2/lib/libSDL2.dylib -lm -liconv -lobjc

$(DOBJ)/%.o: $(DSRC)/%.c $(DINC)
		@$(MKDIR) $(DOBJ)
			$(CC) $(WFLAGS) -c $< $(FINCLIB) $(FINCLIBX) -o $@

libsdl2:
		unzip ./SDL2-2.0.5.zip
		mkdir SDL2
		cd ./SDL2 && ../SDL2-2.0.5/configure --prefix=`pwd`
		make -j8 -C SDL2
		make -C SDL2 install
		rm -rf SDL2-2.0.5

libsdl2_img:
		unzip ./SDL2_image-2.0.1.zip
		sdl2=`cd sdl2/bin && pwd`
		PATH=`echo $PATH:$sdl2`
		cd ./SDL2 && ../SDL2_image-2.0.1/configure --prefix=`pwd`
		make -j8 -C SDL2
		make -C SDL2 install
		rm -rf SDL2_image-2.0.1

libft:
		@if [ -f $(LIBSDL2) ] ; then echo "Nothing to be done" ; else make libsdl2 ; fi
		@if [ -f $(LIBSDL2_IMG) ] ; then echo "Nothing to be done" ; else make libsdl2_img ; fi
		make -C $(DLIB)
		make -C $(DLIBX)
		make -C $(DVECT)

clean:
		make -C $(DLIB) clean
		make -C $(DVECT) clean
			$(RM) $(DOBJ)

fclean: clean
		make -C $(DLIB) fclean
		make -C $(DVECT) fclean
			$(RM) $(NAME)

fcleanlib:
		rm -rf SDL2 SDL2-2.0.5 SDL2_image-2.0.1
		make -C $(DLIBX) clean

ffclean: fclean fcleanlib

re: fclean all

relib: fclean fcleanlib
		make

.PHONY: all libft clean fclean re
