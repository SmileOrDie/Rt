/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/22 16:53:02 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_parse_obj			*srch_obj(t_envg *e, int id)
{
	t_parse_obj *obj_lst;

	obj_lst = e->e->parse_obj;
	while (obj_lst)
	{

		if (obj_lst->obj.id == id)
			return (obj_lst);
		obj_lst = obj_lst->next;
	}
	return (NULL);
}

t_parse_light		*srch_light(t_envg *e, int id)
{
	t_parse_light *light_lst;
	int index;

	index = 0;
	light_lst = e->e->parse_light;
	while (light_lst)
	{
		if (index == id)
			return (light_lst);
		light_lst = light_lst->next;
		index++;
	}
	return (NULL);
}

static void			reset_line(char **line)
{
	int i;
	int len;

	i = 0;
	while (++i <= 15)
	{
		len = ft_strlen(line[i]);
		while (len >= 0)
			line[i][len--] = '\0';
	}
	len = ft_strlen(line[31]);
	while (len >= 0)
		line[31][len--] = '\0';
}

t_light				new_light(t_envg *e)
{
	t_light l;

	l.pos = new_v(ft_atof(e->line[3]), ft_atof(e->line[4]), ft_atof(e->line[5]));
	l.color = (t_color2){ft_atoi(e->line[9]), ft_atoi(e->line[10]), ft_atoi(e->line[11]), 0};
	l.name = ft_strdup(e->line[2]);
	return(l);
}

t_obj				new_obj(t_envg *e)
{
	t_obj obj;

	(!ft_strcmp(e->line[1], "sphere")) ? obj.type = 1 : 0;
	(!ft_strcmp(e->line[1], "plane")) ? obj.type = 2 : 0;
	(!ft_strcmp(e->line[1], "cylinder")) ? obj.type = 3 : 0;
	(!ft_strcmp(e->line[1], "cone")) ? obj.type = 4 : 0;
	(!ft_strcmp(e->line[1], "circle")) ? obj.type = 5 : 0;
	(!ft_strcmp(e->line[1], "square")) ? obj.type = 6 : 0;
	(!ft_strcmp(e->line[1], "cube")) ? obj.type = 7 : 0;
	(!ft_strcmp(e->line[1], "cone_l")) ? obj.type = 8 : 0;
	(!ft_strcmp(e->line[1], "cylinder_l")) ? obj.type = 9 : 0;
	obj.id = e->e->nb_obj;
	obj.radius = ft_atof(e->line[12]);
	obj.ind_refrac = ft_atof(e->line[14]);
	obj.ind_reflec = ft_atof(e->line[15]);
	obj.angle = ft_atof(e->line[31]);
	obj.name = ft_strdup(e->line[2]);
	obj.ind_transp = ft_atof(e->line[13]);
	obj.color = (t_color2){ft_atoi(e->line[9]), ft_atoi(e->line[10]), ft_atoi(e->line[11]), 0};
	obj.pos = new_v(ft_atof(e->line[3]), ft_atof(e->line[4]), ft_atof(e->line[5]));
	obj.dir = new_v(ft_atof(e->line[6]), ft_atof(e->line[7]), ft_atof(e->line[8]));
	obj.id_texture = e->line[30][0];
	obj.group = (!ft_strcmp(e->line[1], "cube")) ? e->e->group_max++ : 0;
	e->e->nb_obj++;
	return(obj);
}

static void			creat_light(t_envg *e)
{
	t_parse_light *b;
	t_parse_light *new;

	if (!(new = (t_parse_light *)malloc(sizeof(t_parse_light))))
		ft_error(MALLOC, "new_l -> inteface_create_obj.h");
	new->light = new_light(e);
	new->next = NULL;
	b = e->e->parse_light;
	if (b)
	{
		while (b->next)
			b = b->next;
		b->next = new;
	}
	else
		e->e->parse_light = new;
}

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

t_vector		creat_cam_2(t_envg *e, int i)
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

void			creat_cam(t_envg *e)
{
	free(e->e->cam);
	e->e->mlx->w = ft_atof(e->line[25]);
	e->e->mlx->h = ft_atof(e->line[26]);
	(!(e->e->cam = (t_cam *)malloc(sizeof(t_cam)))) ? ft_error(MALLOC, "creat_cam") : 0;
	e->e->cam->eye = new_v(ft_atof(e->line[19]), ft_atof(e->line[20]), ft_atof(e->line[21]));
	e->e->cam->l_at = new_v(ft_atof(e->line[22]), ft_atof(e->line[23]), ft_atof(e->line[24]));
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
	e->e->cam->l = creat_cam_2(e, 0);;
}
