/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 18:21:56 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/28 14:41:48 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_color2			get_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color2		color;

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

static void			add_light(char **line, t_env *e)
{
	t_parse_light *parse_light_end;
	t_parse_light *parse_light_b;

	parse_light_b = e->parse_light;
	while (parse_light_b && parse_light_b->next)
		parse_light_b = parse_light_b->next;
	if (!(parse_light_end = 
		(t_parse_light *)malloc(sizeof(t_parse_light))))
		ft_error(MALLOC, "creat_lst -> parce.c");
	parse_light_end->light.pos = new_v(ft_atof(line[4]), ft_atof(line[5])
		, ft_atof(line[6]));
	parse_light_end->light.color = (t_color2){ft_atof(line[1]) *
		ft_atof(line[7]) * 255, ft_atof(line[2]) * ft_atof(line[7]) * 255,
		ft_atof(line[3]) * ft_atof(line[7]) * 255, 0};
	parse_light_end->light.name = (ft_tablen(&line, 0) != 9) ? ft_strdup("light") :
		ft_strdup(line[8]);	
	parse_light_end->next = NULL;
	if (e->parse_light)
		parse_light_b->next = parse_light_end;
	else
		e->parse_light = parse_light_end;
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
