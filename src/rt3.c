/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 11:57:18 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 12:21:53 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			*ft_launch(void *env)
{
	t_env		*tab_env;
	t_env		*e;
	int			i;
	long int	size[3];
	pthread_t	tab_thread[3];
	t_envg		tmp;

	e = (t_env *)env;
	e->coef_t = malloc(sizeof(double) * e->mlx->w * e->mlx->h);
	e->actual_indice = 1;
	if (!(e->tab_three = (t_three **)malloc(sizeof(t_three *) * e->mlx->w * \
	e->mlx->h)))
		ft_error(MALLOC, "ft_launch");
	e->default_indice = 1;
	size[0] = 0;
	size[1] = 0;
	size[2] = 0;
	i = 0;
	e->nb_obj_pix[0] = &(size[0]);
	e->nb_obj_pix[1] = &(size[1]);
	e->nb_obj_pix[2] = &(size[2]);
	tab_env = ft_create_tab_env(*e);
	pthread_create(&tab_thread[0], NULL, boucle, (void *)(&tab_env[0]));
	pthread_create(&tab_thread[1], NULL, boucle, (void *)(&tab_env[1]));
	pthread_create(&tab_thread[2], NULL, boucle, (void *)(&tab_env[2]));
	i = 0;
	while (i < 3)
	{
		pthread_join(tab_thread[i], NULL);
		i++;
	}
	size[0] = *(e->nb_obj_pix[0]) + *(e->nb_obj_pix[1]) + *(e->nb_obj_pix[2]);
	if (!(e->tab_light = (t_l_obj *)malloc(sizeof(t_l_obj) * size[0])))
		ft_error(MALLOC, "ft_launch");
	if (size[0] > 0)
	{
		get_l_tab(e);
		ft_launch_calc(e, e->cl_e->cl);
		get_image(e);
		e->filter_t != NULL ? e->filter_t(e, 0, 0) : 0;
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
		tmp.e = e;
		(e->b_screen == 1) ? keypress('0', &tmp) : mlx_do_sync(e->mlx->mlx);
	}
	e->b_screen = 0;
	i = 0;
	while (i < e->mlx->h * e->mlx->w)
	{
		free_branch(e->tab_three[i]);
		i++;
	}
	free(e->tab_three);
	free(e->tab_light);
	init_id(e);
	pthread_exit(NULL);
}

void		get_matrice(t_vector dir, t_vector **mat)
{
	t_vector mat_x;
	t_vector mat_y;
	t_vector mat_z;

	vnorm(&dir);
	mat_x.x = 1;
	mat_x.y = 0;
	mat_x.z = 0;
	mat_y.x = 0;
	mat_y.y = 1;
	mat_y.z = 0;
	mat_z.x = 0;
	mat_z.y = 0;
	mat_z.z = 1;
	mat_x = vrot(vcross(dir, (t_vector){1, 0, 0, 0}), acos(vpscal(dir, \
		(t_vector){1, 0, 0, 0})) / M_PI * 180, mat_x);
	mat_y = vrot(vcross(dir, (t_vector){0, 1, 0, 0}), acos(vpscal(dir, \
		(t_vector){0, 1, 0, 0})) / M_PI * 180, mat_y);
	mat_z = vrot(vcross(dir, (t_vector){0, 0, 1, 0}), acos(vpscal(dir, \
		(t_vector){0, 0, 1, 0})) / M_PI * 180, mat_z);
	(*mat)[0] = mat_x;
	(*mat)[1] = mat_y;
	(*mat)[2] = mat_z;
}

void		get_obj_lst(t_env *e, t_obj obj, int *i)
{
	int			nb;
	t_vector	*mat;

	nb = 0;
	if (obj.type == 7)
	{
		mat = malloc(sizeof(t_vector) * 3);
		get_matrice(obj.dir, &mat);
		e->l_obj[*i] = obj;
		e->l_obj[*i].id = *i;
		e->l_obj[*i].type = 6;
		e->l_obj[*i].dir = mat[0];
		e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(e->l_obj[*i].dir, \
			obj.radius / 2));
		(*i)++;
		e->l_obj[*i] = obj;
		e->l_obj[*i].type = 6;
		e->l_obj[*i].group = obj.group;
		e->l_obj[*i].dir = vmult_dbl(mat[0], -1);
		e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(e->l_obj[*i].dir, \
			obj.radius / 2));
		e->l_obj[*i].id = *i;
		(*i)++;
		e->l_obj[*i] = obj;
		e->l_obj[*i].id = *i;
		e->l_obj[*i].type = 6;
		e->l_obj[*i].dir = mat[1];
		e->l_obj[*i].pos = vadd(obj.pos, vmult_dbl(e->l_obj[*i].dir, \
			obj.radius / 2));
	}
}
