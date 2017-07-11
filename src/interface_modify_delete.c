/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_modify_delete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:04:26 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/11 16:22:32 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

static	void	ft_strcpy_nbr(char **dest, double d)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	double	neg;

	neg = (d < 0) ? -1.0 : 1.0;
	tmp = ft_itoa((int)d);
	d = (d - ((int)d * neg));
	if (d > 0)
	{
		tmp2 = ft_strjoin(tmp, ".");
		free(tmp);
		tmp3 = ft_itoa(d * 10000);
		tmp = ft_strjoin(tmp2, tmp3);
		free(tmp3);
		free(tmp2);
	}
	ft_strcpy(*dest, tmp);
	free(tmp);
}

void			modif_light(t_envg *e, int light)
{
	t_parse_light *b;

	load_img(e, 3);
	e->f_key = 0;
	e->volet = (t_tab_valid){0, 0, 1, 0, 0};
	b = srch_light(e, light);
	ft_strcpy(e->line[1], "light");
	ft_strcpy(e->line[2], b->light.name);
	ft_strcpy_nbr(&(e->line[3]), b->light.pos.x);
	ft_strcpy_nbr(&(e->line[4]), b->light.pos.y);
	ft_strcpy_nbr(&(e->line[5]), b->light.pos.z);
	ft_strcpy(e->line[6], "-\0\0");
	ft_strcpy(e->line[7], "-\0\0");
	ft_strcpy(e->line[8], "-\0\0");
	ft_strcpy_nbr(&(e->line[9]), b->light.color.r);
	ft_strcpy_nbr(&(e->line[10]), b->light.color.g);
	ft_strcpy_nbr(&(e->line[11]), b->light.color.b);
	ft_strcpy(e->line[12], "-\0\0");
	ft_strcpy(e->line[13], "-\0\0");
	ft_strcpy(e->line[14], "-\0\0");
	ft_strcpy(e->line[15], "-\0\0");
	ft_strcpy(e->line[31], "-\0\0");
	conf_tab(e);
}

void			modif_list2(t_envg *e, t_parse_obj *obj_s)
{
	ft_strcpy(e->line[2], obj_s->obj.name);
	ft_strcpy_nbr(&(e->line[3]), obj_s->obj.pos.x);
	ft_strcpy_nbr(&(e->line[4]), obj_s->obj.pos.y);
	ft_strcpy_nbr(&(e->line[5]), obj_s->obj.pos.z);
	ft_strcpy_nbr(&(e->line[6]), obj_s->obj.dir.x);
	ft_strcpy_nbr(&(e->line[7]), obj_s->obj.dir.y);
	ft_strcpy_nbr(&(e->line[8]), obj_s->obj.dir.z);
	ft_strcpy_nbr(&(e->line[9]), obj_s->obj.color.r);
	ft_strcpy_nbr(&(e->line[10]), obj_s->obj.color.g);
	ft_strcpy_nbr(&(e->line[11]), obj_s->obj.color.b);
	ft_strcpy_nbr(&(e->line[12]), obj_s->obj.radius);
	ft_strcpy_nbr(&(e->line[13]), obj_s->obj.ind_transp);
	ft_strcpy_nbr(&(e->line[14]), obj_s->obj.ind_refrac);
	ft_strcpy_nbr(&(e->line[15]), obj_s->obj.ind_reflec);
}

void			modif_list(t_envg *e, int obj)
{
	char			*type_obj[15];
	t_parse_obj		*obj_s;

	type_obj[0] = "sphere";
	type_obj[1] = "plane";
	type_obj[2] = "cylinder";
	type_obj[3] = "cone";
	type_obj[4] = "circle";
	type_obj[5] = "square";
	type_obj[6] = "cube";
	type_obj[7] = "cone_l";
	type_obj[8] = "cylinder_l";
	load_img(e, 3);
	e->f_key = 0;
	e->volet = (t_tab_valid){0, 0, 1, 0, 0};
	obj_s = srch_obj(e, obj);
	ft_strcpy(e->line[1], type_obj[(obj_s->obj.type - 1)]);
	modif_list2(e, obj_s);
	e->line[30][0] = obj_s->obj.id_texture;
	e->line[30][1] = obj_s->obj.negatif;
	ft_strcpy_nbr(&(e->line[31]), obj_s->obj.angle);
	conf_tab(e);
}

void			modif_default(t_envg *e)
{
	if (!e->e->cam)
	{
		ft_strcpy_nbr(&(e->line[19]), 0);
		ft_strcpy_nbr(&(e->line[20]), 0);
		ft_strcpy_nbr(&(e->line[21]), 0);
		ft_strcpy_nbr(&(e->line[22]), 0);
		ft_strcpy_nbr(&(e->line[23]), 0);
		ft_strcpy_nbr(&(e->line[24]), 0);
		ft_strcpy_nbr(&(e->line[25]), 0);
		ft_strcpy_nbr(&(e->line[26]), 0);
		return ;
	}
	ft_strcpy_nbr(&(e->line[19]), e->e->cam->eye.x);
	ft_strcpy_nbr(&(e->line[20]), e->e->cam->eye.y);
	ft_strcpy_nbr(&(e->line[21]), e->e->cam->eye.z);
	ft_strcpy_nbr(&(e->line[22]), e->e->cam->l_at.x);
	ft_strcpy_nbr(&(e->line[23]), e->e->cam->l_at.y);
	ft_strcpy_nbr(&(e->line[24]), e->e->cam->l_at.z);
	ft_strcpy_nbr(&(e->line[25]), e->e->mlx->w / e->e->anti_a);
	ft_strcpy_nbr(&(e->line[26]), e->e->mlx->h / e->e->anti_a);
}
