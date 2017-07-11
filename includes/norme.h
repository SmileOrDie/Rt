/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:18:07 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/10 17:42:15 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORME_H
# define NORME_H

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
# include "../includes/interface_rt.h"

typedef struct				s_norme
{
	int						x;
	int						y;
	int						i;
	int						s;
	t_parse_obj				*b;
}							t_norme;

typedef struct				s_norme1
{
	double					b;
	double					d;
	double					t0;
	double					t1;
	double					a;
}							t_norme1;

typedef struct				s_norme2
{
	double					t0;
	double					t1;
	double					a;
	double					b;
	double					c;
	t_vector				dp;
	t_vector				tmp;
	t_vector				tmp2;
}							t_norme2;

typedef struct				s_norme3
{
	double					alpha;
	t_vector				origin;
	t_vector				tmp1;
	t_vector				tmp2;
	t_vector				dir_dir;
	t_vector				o_dir;
}							t_norme3;

typedef struct				s_norme5
{
	double					d;
	double					nd;
	double					te;
	t_vector				p_hit;
	t_vector				u;
	t_vector				cross;
}							t_norme5;

typedef struct				s_norme6
{
	int						err;
	char					*source[5];
	char					*namefile[5];
	int						i;
	size_t					len;
	char					buffer[100000];
}							t_norme6;

typedef struct				s_norme7
{
	size_t					global[1];
	int						err;
}							t_norme7;

typedef struct				s_norme9
{
	char					*path;
	char					**new;
	int						y;
}							t_norme9;

typedef struct				s_norme8
{
	int						y;
	int						tmp;
}							t_norme8;

typedef struct				s_norme4
{
	int						id;
	int						group;
	char					*rez;
}							t_norme4;

typedef struct				s_norme10
{
	t_parse_obj				*parse_obj_b;
	t_parse_light			*parse_light_b;
	int						i;
}							t_norme10;

typedef struct				s_norme11
{
	int						y;
	int						x;
	t_vector				p_cam;
	t_vector				v_ray;
	t_env					*e;
}							t_norme11;

typedef struct				s_norme12
{
	int						i;
	int						tx;
	int						ty;
	int						tmpx;
	int						tmpy;
	t_color2				pixel;
	char					flag;
	unsigned char			*img;
	int						color[3];
}							t_norme12;

typedef struct				s_norme13
{
	t_env					*tab_env;
	t_env					*e;
	int						i;
	long int				size[3];
	pthread_t				tab_thread[3];
	t_envg					tmp;
}							t_norme13;

typedef struct				s_norme14
{
	int						x;
	char					*path;
	struct stat				test;
}							t_norme14;

typedef struct				s_norme15
{
	t_vector				*mat;
}							t_norme15;

typedef struct				s_norme16
{
	t_parse_obj				*tmp;
	t_parse_obj				*rez;
	t_obj					obj;
	int						search;
}							t_norme16;

int							sphere_check(char **def);
int							circle_check(char **def);

t_obj						new_obj(t_envg *e);
t_parse_obj					*srch_obj(t_envg *e, int id);
t_parse_light				*srch_light(t_envg *e, int id);
void						reset_line(char **line);
t_light						new_light(t_envg *e);
void						creat_light(t_envg *e);
void						init_pos_value(t_envg *e);
int							add_texture(t_envg *e);
void						clean_str(char **clean, int f);
int							failed_texture(t_envg *e, int i, int x);

void						del_light(t_envg *e, int i);
void						init_id(t_env *e);
void						del_obj(t_envg *e, int i);
void						del_elem(t_envg *e, int i);
void						del_light2(t_parse_light *b, t_parse_light *f_l);

int							select_pos(t_envg *e, int x, int y);
void						volet_target(t_envg *e);
int							interface_mouse_click(int button, int x, int y, \
	t_envg *e);
void						ft_exit(t_envg *e);
void						init_mlx1(t_envg *e);
void						event_touch(t_envg *e);
void						mousse_click_x(t_envg *e, int x);

void						put_img2(t_envg *e, int i, int pos_x, int pos_y);
void						put_img1(t_envg *e, int x, int y);
void						put_img3(t_envg *e);

double						return_dist(t_obj obj, t_vector p_ray, \
	t_vector v_ray);
double						inter_obj(t_env *e, t_vector p_ray, t_vector v_ray,\
	int *id);
t_vector					get_refrac(t_env *e, t_vector v_norm, \
	t_vector v_dir, double ind_refrac);
t_vector					get_reflec(t_vector v_norm, t_vector v_dir);
t_color2					l_shine(t_color2 c, t_color2 color, double angle);
t_color2					mult_color(t_color2 c, double coef);
void						add_branch(t_three *n_branch, t_vector p_hit, \
	double coef, t_color2 c_origin);
t_vector					return_v_norm(int type, t_obj obj, t_vector p_hit);
int							search_obj(t_parse_obj **list_obj, t_obj obj);

t_env						*ft_create_tab_env(t_env e);
double						get_l_pix(t_three *branch, t_l_obj *tab_light, \
	t_obj *l_obj, char flag);
void						*boucle(void *env);
void						free_branch(t_three *branch);
void						get_l_tab(t_env *e);

t_color2					get_pixel(t_three *branch, t_color2 pixel, \
	t_env_cl *e, char flag, double coef_t);
void						get_image(t_env *e);

void						get_matrice(t_vector dir, t_vector **mat);
void						get_obj_lst(t_env *e, t_obj obj, int *i);

void						add_new_texture2(t_envg *e, char **new, int y);
void						add_new_texture(t_envg *e);

void						ft_launch_calc(t_env *e, t_opencl *cl);
void						ft_launch_calc2(t_env *e, t_opencl *cl, t_norme7 n);
void						ft_launch_calc3(t_env *e, t_opencl *cl, t_norme7 n);
void						ft_init_opencl(t_env *e, t_opencl *cl);
int							ft_init_opencl2(t_opencl *cl, char *namefile[5]);
void						init_cl_e(t_env *e, t_env_cl *cl);
char						*ft_create_source(char *file_name);

void						add_obj23_1(t_env *e, char *line, int *x);
void						add_obj23(char *line, int *x, t_env *e, char *rez);
void						add_obj24(char *line, int *x, t_env *e, char *rez);
void						add_obj2_1(char *line, int *x, t_env *e, \
	t_norme4 n);
void						add_obj2(char *line, int *x, t_env *e, int type);
void						get_texture2(t_norme9 n, t_env *e);
void						get_texture(char *line, int *x, t_env *e);
void						add_obj22_1(t_norme8 n, t_env *e, char *line, \
	int *x);
void						add_obj22(char *line, int *x, t_env *e, char *rez);

void						ft_creat_lst_obj(t_env *e);
void						ft_creat_lst_obj2(t_env *e, t_norme10 n);
void						ft_creat_lst_obj3(t_env *e, t_norme10 n);

void						*boucle(void *env);
void						boucle2(t_norme11 n);

int							get_image3(t_env *e, t_norme12 *n);
void						get_image2(t_env *e, t_norme12 n);

void						*ft_launch(void *env);
void						ft_launch2(t_norme13 *n, void *env);
void						ft_launch3(t_norme13 *n);
void						get_obj_lst2(t_env *e, t_obj obj, int *i, \
	t_vector *mat);

#endif
