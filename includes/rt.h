/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:45:45 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/07 16:22:42 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libft/includes/libft.h"
# include "../vector/includes/vector.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <OpenCL/opencl.h>
# include <sys/stat.h>
# include <string.h>
# include <math.h>
# include <pthread.h>

# define ESC 53

# define W 650
# define H 480

# define T 2000000

# define NUMBER_ARG "number of argument not right : "
# define FILES_E "No such file : "
# define MALLOC "failed function malloc in : "
# define ARG_N "argument can't be -NULL- in : "
# define MLX "mlx failed : "
# define KERNEL "error CL_function : "

# define OBJ_I "Invalid object : "
# define J_SON "error format j_son : "
# define N_NUM "Not a number : "
# define CAM "Too many cameras in: "

# define S_MALLOC 0
# define STR_MALLOC "il faut securiser ce malloc! ou?"

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

typedef struct		s_color2
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	vide;
}					t_color2;

typedef	struct		s_obj
{
	int				type;
	int				id;
	double			radius;
	double			ind_refrac; // 1 -> +
	double			ind_reflec; // 0 -> 1
	t_vector		pos;
	t_vector		dir;
	t_vector		point; //verif utilite
	double			angle;
	char			*name;
	double			ind_transp; //0 -> 1
	t_color2		color;
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

typedef struct		s_three
{
	t_color2		c_origin;
	int 			id;
	t_vector		p_hit;
	struct	s_three *r_reflec;
	struct	s_three *r_refrac;
}					t_three;

typedef struct		s_l_obj
{
	int				id;
	double			p_hit_x;
	double			p_hit_y;
	double			p_hit_z;
}					t_l_obj;

typedef struct		s_light
{
	t_vector		pos;
	t_color2		color;
	double			vide;
	double			vide2;
	char 			*name;
}					t_light;

typedef struct			s_opencl
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			kernel_program;
	cl_kernel			kernel;
	cl_mem				lst;
	cl_mem				obj;
	cl_mem				light;
	cl_mem				env;
	cl_mem				color_lst;
}						t_opencl;

typedef struct			s_env_cl
{
	t_l_obj				*lst;
	t_color2			*color_lst;
	t_light				*light;
	t_obj				*l_obj;
	int					nb_obj;
	int					nb_light;
	t_opencl			*cl;
	long int			vacuum;
	double 				vacuum2;
}						t_env_cl;

typedef struct				s_parse_light
{
	t_light					light;
	struct s_parse_light	*next;
}							t_parse_light;

typedef struct			s_parse_obj
{
	t_obj				obj;
	struct s_parse_obj	*next;
}						t_parse_obj;

typedef struct			s_env
{
	t_mlx				*mlx;
	t_light				*light;
	t_obj				*l_obj;
	t_parse_obj			*parse_obj;
	t_parse_light		*parse_light;
	t_cam				*cam;
	double				amb;
	double				angle;
	int					start;
	t_l_obj				*tab_light;
	int					nb_obj;
	int					nb_light;
	double				default_indice;
	double				actual_indice;
	long int			*nb_obj_pix[3];
	t_three				**tab_three;
	int					flag;
	t_env_cl			*cl_e;
}						t_env;

void				*ft_launch(void *env);

void				ft_parse(char *name_file, t_env *e);

int					redcross(t_env *e);

t_obj				add_obj(char **line, int len, int count);

void				add_env(char **line, t_env *e);
void				free_env(t_env *e);

void				ft_error(char *error, char *in);
void				ft_error_var(t_vector v, char *str, int f);

t_color2			get_color(unsigned char r, unsigned char g, unsigned char b);

void				creat_lst(char **line, t_env *e, int count);

void				ft_launch_calc(t_env *e, t_opencl *cl);
void				ft_creat_lst_obj(t_env *e);
void				ft_init_opencl(t_env *e, t_opencl *cl);

// void				start_cl(t_env *e, t_opencl *cl, t_env *tab_env);

double				inter_sphere(t_obj sp, t_vector o, t_vector dir);
double				inter_plane(t_obj sp, t_vector o, t_vector dir);
double				inter_circle(t_obj sp, t_vector o, t_vector dir);
double				inter_square(t_obj sp, t_vector o, t_vector dir);
double				inter_cylinder(t_obj sp, t_vector o, t_vector dir);
double				inter_cone(t_obj sp, t_vector o, t_vector dir);

t_color2			add_color(t_color2 c1, t_color2 c2);
t_color2			mult_color(t_color2 c, double coef);
t_vector			ft_angle_sphere(t_obj s, t_vector v_1);
t_vector			ft_angle_plane(t_obj p, t_vector v_1);
t_vector			ft_angle_circle(t_obj p, t_vector v_1);
t_vector			ft_angle_square(t_obj p, t_vector v_1);
t_vector			ft_angle_cylinder(t_obj s, t_vector v_1);
t_vector			ft_angle_cone(t_obj s, t_vector v_1);

t_obj				add_obj_end(char **line, int len, int count);

void				ft_raytracer(t_env *e, t_color2 pixel, t_vector p_ray, t_vector v_ray, int prof, double coef, t_color2 c_origin, t_three **three);

/*
** interface_graphic.c
*/
void				graphic_interface(t_env *scene);


/*
**	/parcer/parser_*.c
*/
void				free_space(char *line, int *x);
int					get_string(char *line, int *x, char **str);
int					get_number(char *line, int *x);
void				add_obj2(char *line, int *x, t_env *e, int type);
t_vector			get_t_vector(char *line, int *x);
t_color2			get_t_color(char *line, int *x);
int					get_object(char *line, int *x, t_env *e, char *name);
int					get_true(char *line, int *x);
int					get_false(char *line, int *x);
int					get_null(char *line, int *x);
void				parse_json(char *line, t_env *e);
int					count_object(char *line);
void				ft_parse_j(char *name, t_env *e);
void 				exit_error(char *str);
void				get_camera(char *line, int *x, t_env *e);
double				ft_for_atof(char *line, int y, int x);
void				get_ambient(char *line, int *x, t_env *e);
void				get_light(char *line, int *x, t_env *e);
void				get_image_size(char *line, int *x, t_env *e);
void				ft_parse_json(char *line, t_env *e);

#endif