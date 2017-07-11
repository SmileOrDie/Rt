/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/10 19:34:58 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

static void			creat_obj(t_envg *e)
{
	t_parse_obj *b;
	t_parse_obj *new;

	if (!(new = (t_parse_obj *)malloc(sizeof(t_parse_obj))))
		ft_error(MALLOC, "new -> inteface_create_obj.h");
	new->obj = new_obj(e);
	new->next = NULL;
	b = e->e->parse_obj;
	if (b)
	{
		while (b->next)
			b = b->next;
		b->next = new;
	}
	else
		e->e->parse_obj = new;
}

void				creat_elem(t_envg *e)
{
	if ((e->error = check_var_obj(e->line)) != -1)
		return ;
	if (!ft_strcmp("light", e->line[1]))
		creat_light(e);
	else
		creat_obj(e);
	reset_line(e->line);
}

t_vector			creat_cam_2(t_envg *e, int i)
{
	if (i == 1)
		return (new_v(e->e->cam->up.y * e->e->cam->n.z - e->e->cam->up.z *
		e->e->cam->n.y, e->e->cam->up.z * e->e->cam->n.x - e->e->cam->up.x *
		e->e->cam->n.z, e->e->cam->up.x * e->e->cam->n.y - e->e->cam->up.y *
		e->e->cam->n.x));
	else if (i == 0)
		return (new_v(e->e->cam->c.x - e->e->cam->u.x * (e->e->cam->w / 2) -
		e->e->cam->up.x * (e->e->cam->h / 2), e->e->cam->c.y - e->e->cam->u.y *
		(e->e->cam->w / 2) - e->e->cam->up.y * (e->e->cam->h / 2),
		e->e->cam->c.z - e->e->cam->u.z * (e->e->cam->w / 2) -
		e->e->cam->up.z * (e->e->cam->h / 2)));
		return (new_v(0, 0, 0));
}

void				creat_cam(t_envg *e)
{
	free(e->e->cam);
// <<<<<<< HEAD
// 	e->e->mlx->w = ft_atof(e->line[25]);
// 	e->e->mlx->h = ft_atof(e->line[26]);
// 	(!(e->e->cam = (t_cam *)malloc(sizeof(t_cam)))) ? ft_error(MALLOC, \
// 		"creat_cam") : 0;
// 	e->e->cam->eye = new_v(ft_atof(e->line[19]), ft_atof(e->line[20]), \
// 	ft_atof(e->line[21]));
// 	e->e->cam->l_at = new_v(ft_atof(e->line[22]), ft_atof(e->line[23]), \
// 	ft_atof(e->line[24]));
// =======
	e->e->mlx->w = ft_atof(e->line[25]) * e->e->anti_a;
	e->e->mlx->h = ft_atof(e->line[26]) * e->e->anti_a;
	(!(e->e->cam = (t_cam *)malloc(sizeof(t_cam)))) ? ft_error(MALLOC, "creat_cam") : 0;
	e->e->cam->eye = new_v(ft_atof(e->line[19]), ft_atof(e->line[20]), ft_atof(e->line[21]));
	e->e->cam->l_at = new_v(ft_atof(e->line[22]), ft_atof(e->line[23]), ft_atof(e->line[24]));
// >>>>>>> master
	e->e->cam->up = new_v(0.0, -1.0, 0.0);
	vnorm(&e->e->cam->up);
	e->e->cam->fov = 60.0;
	e->e->cam->dist = 150.0;
	e->e->cam->n = vsub(e->e->cam->eye, e->e->cam->l_at);
	vnorm(&e->e->cam->n);
	e->e->cam->u = creat_cam_2(e, 1);
	e->e->cam->h = tan(M_PI * (e->e->cam->fov / 2) / 180) * 2 * e->e->cam->dist;
	e->e->cam->w = e->e->cam->h * ((float)e->e->mlx->w / e->e->mlx->h);
	e->e->cam->c = new_v(e->e->cam->eye.x - e->e->cam->n.x * e->e->cam->dist,
		e->e->cam->eye.y - e->e->cam->n.y * e->e->cam->dist,
		e->e->cam->eye.z - e->e->cam->n.z * e->e->cam->dist);
	e->e->cam->l = creat_cam_2(e, 0);
}
