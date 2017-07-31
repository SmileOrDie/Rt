/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_modify_delete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:04:26 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/13 18:47:58 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

void			init_id(t_env *e)
{
	int			i;
	t_parse_obj	*b;

	i = 0;
	b = e->parse_obj;
	if (b)
	{
		e->parse_obj->obj.id = 0;
		while (b)
		{

			b->obj.id = i++;
			if (b->obj.type == 7)
				i += 5;
			else if (b->obj.type == 8)
				i++;
			else if (b->obj.type == 9)
				i += 2;
			b = b->next;
		}
	}
	e->nb_obj = i;
}

void			del_elem(t_envg *e, int i)
{
	if (e->light >= 0)
		del_light(e, i);
	else
		del_obj(e, i);
}//	ft_creat_lst_obj(e->e);

void			ft_strcpy_nbr(char **dest, double d)
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
	t_parse_light	*b;

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
