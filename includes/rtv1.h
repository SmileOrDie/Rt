/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:45:45 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/23 13:53:29 by shamdani         ###   ########.fr       */
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
# include <pthread.h>
# include <sys/time.h>

# define ESC 53

# define W 650
# define H 480
# define VAL 156000
# define T 2000000

# define NUMBER_ARG "number of argument not right :"
# define FILES_E "No such file : "
# define MALLOC "failed function malloc in :"
# define ARG_N "argument can't be -NULL- in :"
# define MLX "mlx failed :"

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img4;
	unsigned char	*data;
	unsigned char	*data4;
	int				bpp;
	int				sizeline;
	int				endian;
	int				w;
	int				h;
}					t_mlx;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct		s_sphere
{
	t_vector		*pos;
	double			radius;
}					t_sphere;

typedef struct		s_cyl
{
	t_vector		*pos;
	t_vector		*dir;
	double			radius;
}					t_cyl;

typedef struct		s_cone
{
	t_vector		*pos;
	t_vector		*dir;
	double			angle;
	int				m;
}					t_cone;

typedef struct		s_plane
{
	t_vector		*dir;
	t_vector		*point;
}					t_plane;

typedef	struct		s_obj
{
	void			*obj;
	t_color			*color;
	int				(*inter_func)(void *s, t_vector *o, t_vector *dir,
									double *t);
	void			(*angle_func)(void *e, t_vector *o, t_vector *dir);
	struct s_obj	*next;
}					t_obj;

typedef struct		s_cam
{
	t_vector		*eye;
	t_vector		*l_at;
	t_vector		*up;
	double			dist;
	double			fov;
	double			h;
	double			w;
	t_vector		*c;
	t_vector		*l;
	t_vector		*n;
	t_vector		*u;
}					t_cam;

typedef struct		s_light
{
	t_vector		*pos;
	t_vector		*color;
	double			angle;
	t_vector		norm;
	struct s_light	*next;
}					t_light;

typedef struct		s_quad
{
	double			delta;
	double			sqrt_delta;
	double			x0;
	double			x1;
	double			q;
}					t_quad;

typedef struct		s_limit
{
	int				x_start;
	int				x_end;
	int				y_start;
	int				y_end;
}					t_limit;

typedef struct		s_timex
{
	long int		pars;
	long int		ray;
	long int		total;
	int				pars_f;
	int				ray_f;
	int				total_f;
}					t_timex;

typedef struct		s_env
{
	t_mlx			*mlx;
	t_cam			*cam;
	t_light			*light;
	t_light			*d_light;
	t_obj			*l_obj;
	t_obj			*obj;
	t_color			*c_hit;
	t_limit			l;
	double			amb;
	int				flag;
	int				r;
	int				g;
	int				b;
	double			angle;
	t_timex			*chrono;
	int 			nb_thread;
}					t_env;

void				init_mlx(t_env *e);

void				ft_parse(char *name_file, t_env *e);

int					solve_quad(double a, double b, double c, double *t);

int					keypress(int key, t_env *e);
int					redcross(t_env *e);

void				*start_ray(void *e);

t_obj				*add_obj(char **line, int len, int count);

void				add_env(char **line, t_env *e);

int					inter_sphere
(void *s, t_vector *o, t_vector *dir, double *t);
int					inter_plane
(void *s, t_vector *o, t_vector *dir, double *t);
int					inter_cylinder
(void *cylinder, t_vector *o, t_vector *dir, double *t);
int					inter_cone
(void *cone, t_vector *o, t_vector *dir, double *t);

void				ft_error(char *error, char *in);
void				ft_error_var(t_vector *v, char *str, int f);

void				time_mode(char *str, t_env *e);

// t_env				*save_env(t_env *e);
void				pthread_ray(t_env *e);

void				ft_angle_sphere(void *e, t_vector *hit, t_vector *dir_l);
void				ft_angle_plane(void *e, t_vector *np, t_vector *dir_l);
void				ft_angle_cylinder
(void *env, t_vector *hit, t_vector *dir_l);
void				ft_angle_cone(void *env, t_vector *hit, t_vector *dir_l);

t_color				*get_color
(unsigned char r, unsigned char g, unsigned char b);
void				put_pixel(int x, int y, t_env *e);

void				*ft_aliasing(void *e);

#endif
