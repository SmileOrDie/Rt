/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:18:07 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 19:47:06 by pde-maul         ###   ########.fr       */
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
#include "../includes/interface_rt.h"



int 				sphere_check(char **def);
int 				circle_check(char **def);

t_obj				new_obj(t_envg *e);
t_parse_obj			*srch_obj(t_envg *e, int id);
t_parse_light		*srch_light(t_envg *e, int id);
void				reset_line(char **line);
t_light				new_light(t_envg *e);
void				creat_light(t_envg *e);
void				init_pos_value(t_envg *e);
int					add_texture(t_envg *e);
void				clean_str(char **clean, int f);
int					failed_texture(t_envg *e, int i, int x);

void				del_light(t_envg *e, int i);
void				init_id(t_env *e);
void				del_obj(t_envg *e, int i);
void				del_elem(t_envg *e, int i);
void				del_light2(t_parse_light *b, t_parse_light *f_l);

int					select_pos(t_envg *e, int x, int y);
void				volet_target(t_envg *e);
int					interface_mouse_click(int button, int x, int y, t_envg *e);
void				ft_exit(t_envg *e);
void				init_mlx1(t_envg *e);
void				event_touch(t_envg *e);
void				mousse_click_x(t_envg *e, int x);

void				put_img2(t_envg *e, int i, int pos_x, int pos_y);
void				put_img1(t_envg *e, int x, int y);
void				put_img3(t_envg *e);

double				return_dist(t_obj obj, t_vector p_ray, t_vector v_ray);
double				inter_obj(t_env *e, t_vector p_ray, t_vector v_ray, int *id);
t_vector			get_refrac(t_env *e, t_vector v_norm, t_vector v_dir, double ind_refrac);
t_vector			get_reflec(t_vector v_norm, t_vector v_dir);
t_color2			l_shine(t_color2 c, t_color2 color, double angle);
t_color2			mult_color(t_color2 c, double coef);
void				add_branch(t_three *n_branch, t_vector p_hit, double coef, t_color2 c_origin);
t_vector			return_v_norm(int type, t_obj obj, t_vector p_hit);
int					search_obj(t_parse_obj **list_obj, t_obj obj);







#endif
