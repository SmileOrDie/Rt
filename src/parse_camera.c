/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:05:13 by pde-maul          #+#    #+#             */
/*   Updated: 2017/10/05 16:52:21 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_cam	g_default_camera = {{0, 0, -300, 0}, {0, 0, 0, 0}, {0, 1, 0, 0}, 60,
{0, 0, 1, 0}, 1};

void		get_camera3(t_envg *e)
{
	e->cam.dir = vsub(e->cam.l_at, e->cam.eye);
	vnorm(&e->cam.dir);
	e->cam.up = vcross(vcross(e->cam.dir, e->cam.up), e->cam.dir);

}

static void	get_camera2(char *line, int *x, t_envg *e, char *name)
{
	int			y;
	int			tmp;

	if ((ft_strcmp(name, "fov") == 0) && ((y = *x) || 1))
	{
		if ((tmp = get_number(line, x)))
			e->cam.fov = ft_for_atof(line, y, *x);
		else
			ft_error(N_NUM, "get_camera2");
	}
}

static void	get_camera1(char *line, int *x, t_envg *e, char *name)
{
	free_space(line, x);
	e->cam.eye = ft_strcmp(name, "pos") == 0 ?
	get_t_vector(line, x, 0) : e->cam.eye;
	e->cam.l_at = ft_strcmp(name, "dir") == 0 ?
	get_t_vector(line, x, 1) : e->cam.l_at;
	e->cam.up = ft_strcmp(name, "up") == 0 ?
	get_t_vector(line, x, 1) : e->cam.up;
}

void		get_camera(char *line, int *x, t_envg *e)
{
	char		*name;

	e->cam = g_default_camera;
	line[*x] != '{' ? ft_error(J_SON, "get_camera") : (*x)++;
	free_space(line, x);
	while (line[*x] && line[*x] != '}')
	{
		get_string(line, x, &name);
		free_space(line, x);
		line[*x] != ':' ? ft_error(J_SON, "get_camera2") : ((*x)++);
		get_camera1(line, x, e, name);
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
