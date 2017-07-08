/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 11:57:18 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/08 12:58:29 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void 				ft_launch2(t_norme13 *n, void *env)
{
	n->e = (t_env *)env;
	n->e->coef_t = malloc(sizeof(double) * n->e->mlx->w * n->e->mlx->h);
	n->e->actual_indice = 1;
	if (!(n->e->tab_three = (t_three **)malloc(sizeof(t_three *) * n->e->mlx->w * \
	n->e->mlx->h)))
		ft_error(MALLOC, "ft_launch");
	n->e->default_indice = 1;
	n->size[0] = 0;
	n->size[1] = 0;
	n->size[2] = 0;
	n->i = 0;
	n->e->nb_obj_pix[0] = &(n->size[0]);
	n->e->nb_obj_pix[1] = &(n->size[1]);
	n->e->nb_obj_pix[2] = &(n->size[2]);
	n->tab_env = ft_create_tab_env(*n->e);
	pthread_create(&n->tab_thread[0], NULL, boucle, (void *)(&n->tab_env[0]));
	pthread_create(&n->tab_thread[1], NULL, boucle, (void *)(&n->tab_env[1]));
	pthread_create(&n->tab_thread[2], NULL, boucle, (void *)(&n->tab_env[2]));
	n->i = 0;
	while (n->i < 3)
	{
		pthread_join(n->tab_thread[n->i], NULL);
		n->i++;
	}
}

void			*ft_launch(void *env)
{
	t_norme13 n;

	ft_launch2(&n, env);
	n.size[0] = *(n.e->nb_obj_pix[0]) + *(n.e->nb_obj_pix[1]) + *(n.e->nb_obj_pix[2]);
	if (!(n.e->tab_light = (t_l_obj *)malloc(sizeof(t_l_obj) * n.size[0])))
		ft_error(MALLOC, "ft_launch");
	if (n.size[0] > 0)
	{
		get_l_tab(n.e);
		ft_launch_calc(n.e, n.e->cl_e->cl);
		get_image(n.e);
		n.e->filter_t != NULL ? n.e->filter_t(n.e, 0, 0) : 0;
		mlx_put_image_to_window(n.e->mlx->mlx, n.e->mlx->win, n.e->mlx->img, 0, 0);
		n.tmp.e = n.e;
		(n.e->b_screen == 1) ? keypress('0', &n.tmp) : mlx_do_sync(n.e->mlx->mlx);
	}
	n.e->b_screen = 0;
	n.i = 0;
	while (n.i < n.e->mlx->h * n.e->mlx->w)
	{
		free_branch(n.e->tab_three[n.i]);
		n.i++;
	}
	free(n.e->tab_three);
	free(n.e->tab_light);
	init_id(n.e);
	pthread_exit(NULL);
}

void			get_matrice(t_vector dir, t_vector **mat)
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

void			get_obj_lst(t_env *e, t_obj obj, int *i)
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
