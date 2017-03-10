/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesprog <ldesprog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:45:45 by shamdani          #+#    #+#             */
/*   Updated: 2017/03/10 18:14:46 by ldesprog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../vector/includes/vector.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
# include <OpenCL/opencl.h>
# include <sys/stat.h>
# include <string.h>

# define ESC 53

# define W 650
# define H 480

# define T 2000000

# define NUMBER_ARG "number of argument not right :"
# define FILES_E "No such file : "
# define MALLOC "failed function malloc in :"
# define ARG_N "argument can't be -NULL- in :"
# define MLX "mlx failed :"

# define S_MALLOC 0
# define STR_MALLOC "il faut securiser ce malloc"

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
	int				w;
	int				h;
	int				crenelage;
}					t_mlx;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				t;
}					t_color;

typedef	struct		s_obj
{
	int				type;
	int				id;
	double			vide2;
	double			vide3;
	double			vide4;
	t_vector		pos;
	t_vector		dir;
	t_vector		point;
	double			radius;
	double			angle;
	t_color			color;
	double			t;
	double			ind_refrac; // 1 -> +
	double			ind_reflec; // 0 -> 1
	double			ind_transp; //0 -> 1
}					t_obj;

typedef struct		s_cam
{
	t_vector		eye;
	t_vector		l_at;
	t_vector		up;
	double			dist;
	double			fov;
	double			h;
	double			w;
	t_vector		c;
	t_vector		l;
	t_vector		n;
	t_vector		u;
}					t_cam;

typedef struct		s_light
{
	t_vector		pos;
	t_vector		color;
	// double			angle;
	// double			vide;
	// double			vide2;
	// double			vide3;
	// t_vector		norm;
}					t_light;

typedef struct			s_opencl
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			kernel_program;
	cl_kernel			kernel;
	cl_mem				data;
	cl_mem				obj;
	cl_mem				light;
	cl_mem				env;
	cl_mem				mlx;
	cl_mem				cam;
}						t_opencl;

typedef struct		s_env
{
	t_mlx			*mlx;
	t_light			*light;
	t_obj			*l_obj;
	t_obj			*tab_transp;
	t_obj			*tab_transp_l;
	void			*vide;
	void			*vide2;
	t_cam			*cam;
	t_obj			obj;
	t_vector		norm;
	t_color			c_hit;
	int				flag;
	double			amb;
	double			angle;
	int				r;
	int				g;
	int				b;
	int				nb_obj;
	int				nb_light;
	double			move;
	double			truc1;
	double			truc2;
	t_opencl		*cl;
}					t_env;

void				ft_parse(char *name_file, t_env *e);

int					keypress(int key, t_env *e);
int					redcross(t_env *e);

t_obj				add_obj(char **line, int len, int count);

void				add_env(char **line, t_env *e);

void				ft_error(char *error, char *in);
void				ft_error_var(t_vector v, char *str, int f);

t_color				get_color(unsigned char r, unsigned char g, unsigned char b);

void				ft_launch_calc(t_env *e, t_opencl *cl);
void				ft_init_opencl(t_env *e, t_opencl *cl, int nb_source, t_env *tab_env);
#endif


