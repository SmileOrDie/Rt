/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:45:45 by shamdani          #+#    #+#             */
/*   Updated: 2017/11/09 13:18:39 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libft/includes/libft.h"
# include "../vector/includes/vector.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <OpenCL/opencl.h>
# include <sys/stat.h>
# include <string.h>
# include <math.h>
# include <pthread.h>
# include "../SDL2/include/SDL2/SDL.h"
# include "../SDL2/include/SDL2/SDL_image.h"

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
# define OBJ_F "error format obj_file : "
# define N_NUM "Not a number : "
# define CAM "Too many cameras in: "

# define S_MALLOC 0
# define STR_MALLOC "il faut securiser ce malloc! ou?"

typedef struct				s_pos
{
	int						w;
	int						h;
}							t_pos;

typedef struct				s_mlx
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*data;
	int						bpp;
	int						sizeline;
	int						endian;
	int						w;
	int						h;
	int						crenelage;
	double					vide;
}							t_mlx;

typedef struct				s_color
{
	int						r;
	int						g;
	int						b;
	int						t;
}							t_color;

typedef struct				s_color2
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
	unsigned char			vide;
}							t_color2;

typedef	struct				s_obj
{
	double					angle;
	double					radius;
	double					ind_refrac;
	double					ind_reflec;
	t_vector				pos;
	t_vector				dir;
	t_vector				point;
	double					ind_transp;
	unsigned short int		group;
	unsigned char			negatif;
	unsigned char			vide;
	char					*name;
	t_color2				color;
	unsigned short int		id;
	unsigned char			type;
	unsigned char			id_texture;
}							t_obj;

typedef struct				s_cam
{
	t_vector				eye;
	t_vector				l_at;
	t_vector				up;
	double					dist;
	double					fov;
	double					h;
	double					w;
	t_vector				c;
	t_vector				l;
	t_vector				n;
	t_vector				u;
	int						set;
	int						view;
}							t_cam;

typedef struct				s_three
{
	t_color2				c_origin;
	int						id;
	t_vector				p_hit;
	struct s_three			*r_reflec;
	struct s_three			*r_refrac;
}							t_three;

typedef struct				s_ray
{
	t_vector				p_ray;
	t_vector				v_ray;
	int						prof;
	double					coef;
	t_color2				c_origin;
}							t_ray;

typedef struct				s_tuff
{
	t_vector				p_hit;
	t_vector				vec;
	t_vector				v_norm;
	int						id;
	int						ret;
}							t_stuff;

typedef struct				s_l_obj
{
	int						id;
	double					p_hit_x;
	double					p_hit_y;
	double					p_hit_z;
}							t_l_obj;

typedef struct				s_light
{
	t_vector				pos;
	t_color2				color;
	double					vide;
	double					vide2;
	char					*name;
}							t_light;

typedef struct				s_opencl
{
	cl_platform_id			platform;
	cl_device_id			device;
	cl_context				context;
	cl_command_queue		command_queue;
	cl_program				kernel_program;
	cl_kernel				kernel;
	cl_mem					*data;
	cl_mem					lst;
	cl_mem					texture;
	cl_mem					obj;
	cl_mem					light;
	cl_mem					env;
	cl_mem					color_lst;
}							t_opencl;

typedef struct				s_env_cl
{
	t_l_obj					*lst;
	t_color2				*color_lst;
	t_light					*light;
	t_obj					*l_obj;
	t_mlx					*texture;
	int						nb_obj;
	int						nb_light;
	t_opencl				*cl;
	int						group_max;
	int						amb;
}							t_env_cl;

typedef struct				s_parse_light
{
	t_light					light;
	struct s_parse_light	*next;
}							t_parse_light;

typedef struct				s_parse_obj
{
	t_obj					obj;
	struct s_parse_obj		*next;
}							t_parse_obj;

typedef struct				s_tab_f
{
	double				vx;
	double				vy;
	double				vz;
	double				vtx;
	double				vty;
	double				vnx;
	double				vny;
	double				vnz;
}							t_tab_f;

typedef struct				s_parse_obj_f
{
	int					start;
	int					v;
	int					vt;
	int					vn;
	t_tab_f				tab;
}							t_parse_obj_f;

typedef struct				s_env
{
	t_mlx					mlx;
	void					**wait_img;
	t_pos					*size;
	t_light					*light;
	t_obj					*l_obj;
	t_cam					cam;
	double					*coef_t;
	double					amb;
	int						b_screen;
	int						start;
	t_l_obj					*tab_light;
	int						nb_obj;
	int						nb_light;
	double					default_indice;
	double					actual_indice;
	long int				*nb_obj_pix[8];
	t_three					**tab_three;
	int						flag;
	int						wait;
	t_pos					win;
	void					(*filter_t)(struct s_env *, int, int);
	t_env_cl				*cl_e;
	t_mlx					*texture;
	int						anti_a;
	int						nb_tex;
	int						group_max;
	t_three					**begin_three;
}							t_env;

void						*ft_launch(void *env);

void						ft_parse(char *name_file, t_env *e);

int							redcross(t_env *e);

t_obj						add_obj(char **line, int len, int count);

void						add_env(char **line, t_env *e);
void						free_env(t_env *e);

void						ft_error(char *error, char *in);
void						ft_error_var(t_vector v, char *str, int f);

t_color2					get_color(unsigned char r, unsigned char g,
	unsigned char b);

void						creat_lst(char **line, t_env *e, int count);

void						ft_launch_calc(t_env *e, t_opencl *cl);

double						inter_sphere(t_obj sp, t_vector o, t_vector dir);
double						inter_plane(t_obj sp, t_vector o, t_vector dir);
double						inter_circle(t_obj sp, t_vector o, t_vector dir);
double						inter_square(t_obj sp, t_vector o, t_vector dir);
double						inter_cylinder(t_obj sp, t_vector o, t_vector dir);
double						inter_cone(t_obj sp, t_vector o, t_vector dir);

t_color2					add_color(t_color2 c1, t_color2 c2);
t_color2					mult_color(t_color2 c, double coef);
t_vector					ft_angle_sphere(t_obj s, t_vector v_1);
t_vector					ft_angle_plane(t_obj p, t_vector v_1);
t_vector					ft_angle_circle(t_obj p, t_vector v_1);
t_vector					ft_angle_square(t_obj p, t_vector v_1);
t_vector					ft_angle_cylinder(t_obj s, t_vector v_1);
t_vector					ft_angle_cone(t_obj s, t_vector v_1);

t_obj						add_obj_end(char **line, int len, int count);

void						ft_raytracer(t_env *e, t_ray ray, t_three **three);

/*
** interface_graphic.c
*/

void						apply_color_pix(t_env *e, int *rgb,
	int x, int y);
int							*lecture_img_for_blur(t_env *e, int x,
	int y, int i);
int							apply_color_pix_for_blur(t_env *e, int *rgb,
	int x, int y);
void						lecture_img(t_env *e, int rgb[5], int x,
	int y);
void						filter_sepia(t_env *e, int x, int y);
void						filter_red(t_env *e, int x, int y);
void						filter_blue(t_env *e, int x, int y);
void						filter_green(t_env *e, int x, int y);
void						filter_blur(t_env *e, int x, int y);

void						ft_parse_obj_files1(char *name, t_env *e);
int							ft_parse_obj_v(char *line, t_env *e);
int							ft_parse_obj_vt(char *line, t_env *e, int i);
int							ft_parse_obj_vn(char *line, t_env *e, int i);
int							ft_parse_obj_f(char *line, t_env *e, int i);
double						ft_check_pow(char *str, int s, int y);
int							ft_len_nb(char *line, int s);

double						ft_atod(char *str);

char						*ft_dtoa(double nb);
t_vector					get_refrac(t_env *e, t_vector d, t_vector v,
	double i);
double						inter_obj(t_env *e, t_vector p_ray, t_vector v,
	int *id);
t_vector					get_reflec(t_vector v_norm, t_vector v_dir);
t_parse_obj					*get_obj_list(t_env *e, t_three *current,
	t_three *branch);
int							ft_get_obj_neg(t_obj obj, t_parse_obj *list_obj);
t_vector					return_v_norm(int type, t_obj obj, t_vector p_hit);
void						add_branch(t_three *n, t_vector p, double d,
	t_color2 c);
int							search_obj(t_parse_obj **list_obj, t_obj obj);

#endif
