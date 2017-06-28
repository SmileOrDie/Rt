/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:18:07 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 16:33:30 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORME_H
# define NORME_H

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




#endif
