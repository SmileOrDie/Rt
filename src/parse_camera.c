/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:05:13 by pde-maul          #+#    #+#             */
/*   Updated: 2017/08/02 18:12:08 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_cam	g_default_camera = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, 60,
	150, 480, 650, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, 1};

void	get_camera3(t_envg *e)
{
	e->cam.n = vsub(e->cam.eye, e->cam.l_at);
	vnorm(&e->cam.n);
	e->cam.u = new_v(e->cam.up.y * e->cam.n.z - e->cam.up.z *
		e->cam.n.y, e->cam.up.z * e->cam.n.x - e->cam.up.x *
		e->cam.n.z, e->cam.up.x * e->cam.n.y - e->cam.up.y *
		e->cam.n.x);
	e->cam.h = tan(M_PI * (e->cam.fov / 2) / 180) * 2 * e->cam.dist;
	e->cam.w = e->cam.h * ((float)e->win.w / e->win.h);
	e->cam.c = new_v(e->cam.eye.x - e->cam.n.x * e->cam.dist,
		e->cam.eye.y - e->cam.n.y * e->cam.dist,
		e->cam.eye.z - e->cam.n.z * e->cam.dist);
	e->cam.l = new_v(e->cam.c.x - e->cam.u.x * (e->cam.w / 2) -
		e->cam.up.x * (e->cam.h / 2), e->cam.c.y - e->cam.u.y *
		(e->cam.w / 2) - e->cam.up.y * (e->cam.h / 2),
		e->cam.c.z - e->cam.u.z * (e->cam.w / 2) - e->cam.up.z *
		(e->cam.h / 2));
}

void	get_camera2(char *line, int *x, t_envg *e, char *name)
{
	int			y;
	int			tmp;

	line[*x] != ':' ? ft_error(J_SON, "get_camera2") : ((*x)++);
	free_space(line, x);
	if (ft_strcmp(name, "pos") == 0)
		e->cam.eye = get_t_vector(line, x, 0);
	if (ft_strcmp(name, "dir") == 0)
		e->cam.l_at = get_t_vector(line, x, 1);
	if (ft_strcmp(name, "up") == 0)
		e->cam.up = get_t_vector(line, x, 1);
	if (ft_strcmp(name, "dist") == 0 && ((y = *x) || 1))
	{
		tmp = get_number(line, x);
		(tmp != 0) ? e->cam.dist = ft_for_atof(line, y, *x) :
			ft_error(N_NUM, "get_camera2 for dist");
	}
	if ((ft_strcmp(name, "fov") == 0) && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			e->cam.fov = ft_for_atof(line, y, *x);
		else
			ft_error(N_NUM, "get_camera2");
	}
}

void	get_camera(char *line, int *x, t_envg *e)
{
	char		*name;

	e->cam = g_default_camera;
	line[*x] != '{' ? ft_error(J_SON, "get_camera") : (*x)++;
	free_space(line, x);
	while (line[*x] && line[*x] != '}')
	{
		get_string(line, x, &name);
		free_space(line, x);
		get_camera2(line, x, e, name);
		free_space(line, x);
		free(name);
		if (line[*x] != ',')
			break ;
		else
			(*x)++;
		free_space(line, x);
	}
	free_space(line, x);
	line[*x] != '}' ? ft_error(J_SON, "get_camera2") : (*x)++;
}
