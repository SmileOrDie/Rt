/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesprog <ldesprog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 18:21:56 by shamdani          #+#    #+#             */
/*   Updated: 2017/03/10 18:19:39 by ldesprog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color			get_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color		color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

static void			add_cam(char **line, t_env *e)
{
	e->cam = (t_cam *)malloc(sizeof(t_cam));
	if (S_MALLOC)
		printf("%s\n", STR_MALLOC);
	e->cam->eye = new_v(ft_atof(line[1]), ft_atof(line[2]), ft_atof(line[3]));
	e->cam->l_at = new_v(ft_atof(line[4]), ft_atof(line[5]), ft_atof(line[6]));
	e->cam->up = new_v(ft_atof(line[7]), ft_atof(line[8]), ft_atof(line[9]));
	vnorm(&e->cam->up);
	e->cam->fov = ft_atoi(line[10]);
	e->cam->dist = ft_atoi(line[11]);
	e->cam->n = vsub(e->cam->eye, e->cam->l_at);
	vnorm(&e->cam->n);
	e->cam->u = new_v(e->cam->up.y * e->cam->n.z - e->cam->up.z *
		e->cam->n.y, e->cam->up.z * e->cam->n.x - e->cam->up.x *
		e->cam->n.z, e->cam->up.x * e->cam->n.y - e->cam->up.y *
		e->cam->n.x);
	e->cam->h = tan(M_PI * (e->cam->fov / 2) / 180) * 2 * e->cam->dist;
	e->cam->w = e->cam->h * ((float)e->mlx->w / e->mlx->h);
	e->cam->c = new_v(e->cam->eye.x - e->cam->n.x * e->cam->dist,
		e->cam->eye.y - e->cam->n.y * e->cam->dist,
		e->cam->eye.z - e->cam->n.z * e->cam->dist);
	e->cam->l = new_v(e->cam->c.x - e->cam->u.x * (e->cam->w / 2) -
		e->cam->up.x * (e->cam->h / 2), e->cam->c.y - e->cam->u.y *
		(e->cam->w / 2) - e->cam->up.y * (e->cam->h / 2),
		e->cam->c.z - e->cam->u.z * (e->cam->w / 2) - e->cam->up.z *
		(e->cam->h / 2));
}

t_light				*ft_increase_nb_light(t_light *light, int nb_light)
{
	t_light *new;
	int i;

	new = (t_light *)malloc(sizeof(t_light) * (nb_light + 1));
	if (S_MALLOC)
		printf("%s\n", STR_MALLOC);
	i = 0;
	if (light)
	{
		while (i < nb_light)
		{
			new[i] = light[i];
			i++;
		}
		free(light);
	}
	return (new);
}

static void			add_light(char **line, t_env *e)
{
	e->light = ft_increase_nb_light(e->light, e->nb_light);
	e->light[e->nb_light].pos = new_v(ft_atof(line[4]), ft_atof(line[5]), ft_atof(line[6]));
	e->light[e->nb_light].color = new_v(ft_atof(line[1]) * ft_atof(line[7]), ft_atof(line[2])
	* ft_atof(line[7]), ft_atof(line[3]) * ft_atof(line[7]));
	// e->light[e->nb_light].angle = 1;
	e->nb_light++;
}

void				add_env(char **line, t_env *e)
{
	if (ft_strcmp(line[0], "light") == 0)
		add_light(line, e);
	else if (ft_strcmp(line[0], "cam") == 0)
	{
		e->flag = 1;
		add_cam(line, e);
	}
	else if (ft_strcmp(line[0], "ambient") == 0)
		e->amb = ft_atof(line[1]);
}
