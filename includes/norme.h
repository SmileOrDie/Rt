/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:18:07 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 15:35:11 by pde-maul         ###   ########.fr       */
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



#endif
