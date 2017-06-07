/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_modify_delete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:04:26 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/20 13:44:46 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
// typedef struct		s_light
// {
// 	t_vector		pos;
// 	t_color2		color;
// 	double			vide;
// 	double			vide2;
// 	char 			*name;
// }					t_light;
void			del_light(t_envg *e, int i)
{
	t_parse_light *b;
	t_parse_light *f_l;

	// t_light a = {{0, 0, 0, 0}, {255, 255, 255, 0}, 0, 0, NULL};
	// t_light c = {{0, 0, 0, 0}, {255, 255, 255, 0}, 0, 0, NULL};

	// c == a ? printf("ca marche\n") : 0;
	b = e->e->parse_light;
	if (i > 0)
	{
		while(b->next)
		{
			if (e->e->light[i].name == b->next->light.name)
			{
				f_l = b->next;
				b->next = f_l->next;
				free(f_l->light.name);
				free(f_l);
				break;
			}
			b = b->next;
		}
	}
	else if (i == 0)
	{
		if (e->e->light[i].name == b->light.name)
			e->e->parse_light = e->e->parse_light->next;
		free(b->light.name);
		free(b);
	}
	ft_creat_lst_obj(e->e);
}

void			init_id(t_env *e)
{
	int i;
	t_parse_obj *b;

	i = 0;
	b = e->parse_obj;
	if (b)
	{	
		e->parse_obj->obj.id = 0;
		while (b)
		{
			b->obj.id = i++;
			b = b->next;
		}
	}
}

void			del_obj(t_envg *e, int i)
{
	t_parse_obj *b;
	t_parse_obj *f_obj;

	b = e->e->parse_obj;
	if (i > 0)
	{
		while(b->next)
		{
			if (e->e->l_obj[i].name == b->next->obj.name)
			{
				f_obj = b->next;
				b->next = f_obj->next;
				free(f_obj->obj.name);
				free(f_obj);
				break;
			}
			b = b->next;
		}
	}
	else if (i == 0)
	{
		if (e->e->l_obj[i].name == b->obj.name)
			e->e->parse_obj = e->e->parse_obj->next;
		free(b->obj.name);
		free(b);
		b = NULL;
	}
	init_id(e->e);
	ft_creat_lst_obj(e->e);
}
void			del_elem(t_envg *e, int i)
{
	if (e->light >= 0)
		del_light(e, i);
	else
		del_obj(e, i);	
}

static	void	ft_strcpy_nbr(char *dest, double d)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	double	neg;

	neg = (d < 0) ? -1 : 1;
	tmp = ft_itoa((int)d);
	d = (d - ((int)d * neg));
	if (d > 0)
	{
		tmp2 = ft_strjoin(tmp, ".");
		free(tmp);
		tmp3 = ft_itoa(d * 1000);
		tmp = ft_strjoin(tmp2,tmp3);
		free(tmp3);
		free(tmp2);
	}
	ft_strcpy(dest, tmp);
	free(tmp);
}

void 		modif_light(t_envg *e, int light)
{
	load_img(e, 3);
	e->f_key = 0;
	e->volet = (t_tab_valid){0, 0, 1, 0, 0};
	ft_strcpy(e->line[1], "light");
	ft_strcpy(e->line[2], e->e->light[light].name);
	ft_strcpy_nbr(e->line[3], e->e->light[light].pos.x);
	ft_strcpy_nbr(e->line[4], e->e->light[light].pos.y);
	ft_strcpy_nbr(e->line[5], e->e->light[light].pos.z);
	ft_strcpy_nbr(e->line[9], e->e->light[light].color.r / 255.0);
	ft_strcpy_nbr(e->line[10], e->e->light[light].color.g / 255.0);
	ft_strcpy_nbr(e->line[11], e->e->light[light].color.b / 255.0);
	ft_strcpy(e->line[12], ".");
	conf_tab(e);
}

void		modif_list(t_envg *e, int obj)
{
	char	*type_obj[15];

	type_obj[0] = "sphere";
	type_obj[1] = "plane";
	type_obj[2] = "cylinder";
	type_obj[3] = "cone";
	type_obj[4] = "circle";
	load_img(e, 3);
	e->f_key = 0;
	e->volet = (t_tab_valid){0, 0, 1, 0, 0};
	ft_strcpy(e->line[1], type_obj[(e->e->l_obj[obj].type - 1)]);
	ft_strcpy(e->line[2], e->e->l_obj[obj].name);
	ft_strcpy_nbr(e->line[3], e->e->l_obj[obj].pos.x);
	ft_strcpy_nbr(e->line[4], e->e->l_obj[obj].pos.y);
	ft_strcpy_nbr(e->line[5], e->e->l_obj[obj].pos.z);
	ft_strcpy_nbr(e->line[6], e->e->l_obj[obj].dir.x);
	ft_strcpy_nbr(e->line[7], e->e->l_obj[obj].dir.y);
	ft_strcpy_nbr(e->line[8], e->e->l_obj[obj].dir.z);
	ft_strcpy_nbr(e->line[9], e->e->l_obj[obj].color.r);
	ft_strcpy_nbr(e->line[10], e->e->l_obj[obj].color.g);
	ft_strcpy_nbr(e->line[11], e->e->l_obj[obj].color.b);
	(e->e->l_obj[obj].type == 1 || e->e->l_obj[obj].type == 3 ||
		e->e->l_obj[obj].type == 5) ?
	ft_strcpy_nbr(e->line[12], e->e->l_obj[obj].radius) : 0;
	(e->e->l_obj[obj].type == 4) ? ft_strcpy_nbr(e->line[12],
		e->e->l_obj[obj].angle) : 0;
	ft_strcpy_nbr(e->line[13], e->e->l_obj[obj].ind_transp);
	ft_strcpy_nbr(e->line[14], e->e->l_obj[obj].ind_refrac);
	ft_strcpy_nbr(e->line[15], e->e->l_obj[obj].ind_reflec);
	conf_tab(e);
}

void		modif_default(t_envg *e)
{
	// cam 0 150 -500 0 0 0 0 -1 0 60 150
	if (!e->e->cam)
	{
	 	ft_strcpy_nbr(e->line[19], 0);
		ft_strcpy_nbr(e->line[20], 0);
		ft_strcpy_nbr(e->line[21], 0);
		ft_strcpy_nbr(e->line[22], 0);
		ft_strcpy_nbr(e->line[23], 0);
		ft_strcpy_nbr(e->line[24], 0);
		ft_strcpy_nbr(e->line[25], 0);
		ft_strcpy_nbr(e->line[26], 0);
		return ;
	}
	ft_strcpy_nbr(e->line[19], e->e->cam->eye.x);
	ft_strcpy_nbr(e->line[20], e->e->cam->eye.y);
	ft_strcpy_nbr(e->line[21], e->e->cam->eye.z);
	ft_strcpy_nbr(e->line[22], e->e->cam->l_at.x);
	ft_strcpy_nbr(e->line[23], e->e->cam->l_at.y);
	ft_strcpy_nbr(e->line[24], e->e->cam->l_at.z);
	ft_strcpy_nbr(e->line[25], e->e->mlx->w);
	ft_strcpy_nbr(e->line[26], e->e->mlx->h);
}
