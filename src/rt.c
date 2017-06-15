/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/14 17:57:45 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void		init(t_env *e)
{
	if (!(e->cl_e = (t_env_cl *)malloc(sizeof(t_env_cl))))
		ft_error(MALLOC, "rtv1.c => int main(...)");
	if (!(e->cl_e->cl = (t_opencl *)malloc(sizeof(t_opencl))))
		ft_error(MALLOC, "rtv1.c => int main(...)");
	if (!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_error(MALLOC, "int	ft_parse(char *name, t_env *e)(e->mlx)");
	e->light = NULL;
	e->l_obj = NULL;
	e->cam = NULL;
	e->mlx->w = W;
	e->mlx->h = H;
	e->amb = 0.1;
	e->nb_obj = 0;
	e->nb_light = 0;
}

t_env			*ft_create_tab_env(t_env e)
{
	t_env	*tab;

	tab = (t_env *)malloc(sizeof(t_env) * 3);
	tab[0] = e;
	tab[1] = e;
	tab[2] = e;
	tab[0].start = 0;
	tab[1].start = 1;
	tab[2].start = 2;
	return (tab);
}


// static void		ft_exit3(t_env *e)
// {
// 	clReleaseKernel(e->cl->kernel);
// 	// clReleaseProgram(e->cl->kernel_program);
// 	clReleaseCommandQueue(e->cl->command_queue);
// 	clReleaseMemObject(e->cl->data);
// 	clReleaseMemObject(e->cl->obj);
// 	clReleaseMemObject(e->cl->light);
// 	clReleaseMemObject(e->cl->env);
// 	clReleaseMemObject(e->cl->mlx);
// 	clReleaseMemObject(e->cl->cam);
// 	clReleaseContext(e->cl->context);
// 	// exit(0);
// }

double				get_l_pix(t_three *branch, t_l_obj *tab_light, t_obj *l_obj, char flag)
{
	static int		i = 0;
	static double	coef_t = 0;


	flag == 2 ? (i = 0) : 0;
	flag ? (coef_t = 0) : 0;
	if (branch && branch->r_reflec)
		get_l_pix(branch->r_reflec, tab_light, l_obj, 0);
	if (branch && branch->r_refrac)
		get_l_pix(branch->r_refrac, tab_light, l_obj, 0);
	if (branch && branch->p_hit.coef * (1 - l_obj[branch->id].ind_transp) * (1 - l_obj[branch->id].ind_reflec) > 0.04)
	{
		// printf("test2 voila\n");
		tab_light[i].id = branch->id;
		tab_light[i].p_hit_x = branch->p_hit.x;
		tab_light[i].p_hit_y = branch->p_hit.y;
		tab_light[i].p_hit_z = branch->p_hit.z;
		coef_t += branch->p_hit.coef * (1 - l_obj[branch->id].ind_transp) * (1 - l_obj[branch->id].ind_reflec);
		i++;
	}
	return (coef_t);

}

void				*boucle(void *env)
{
	int			y;
	int			x;
	t_vector	p_cam;
	t_vector	v_ray;
	t_env		*e;

	e = (t_env *)env;
	y = 0;
	while (y < e->mlx->h)
	{
		x = e->start;
		while (x < e->mlx->w)
		{
			p_cam = new_v(e->cam->l.x + e->cam->u.x * x * (e->cam->w / e->mlx->w) + e->
				cam->up.x * y * (e->cam->h / e->mlx->h), e->cam->l.y + e->cam->u.y *
				x * (e->cam->w / e->mlx->w) + e->cam->up.y * y * (e->cam->h / e->mlx->h)
				, e->cam->l.z + e->cam->u.z * x * (e->cam->w / e->mlx->w) + e->
				cam->up.z * y * (e->cam->h / e->mlx->h));
			v_ray = vsub(p_cam, e->cam->eye);
			vnorm(&v_ray);
			ft_raytracer(e, (t_color2){0, 0, 0, 0}, e->cam->eye, v_ray, 0, 1, (t_color2){255, 255, 255, 0}, &(e->tab_three[x + y * e->mlx->w]));
			x += 3;
		}
		y++;
	}
	pthread_exit(NULL);
}

void				free_branch(t_three *branch)
{
	if (branch)
	{
		free_branch(branch->r_reflec);
		free_branch(branch->r_refrac);
		free(branch);
	}
}

void				get_l_tab(t_env *e)
{
	int		i;
	char	flag;

	i = 0;
	flag = 2;
	while (i < e->mlx->h * e->mlx->w)
	{
		e->coef_t[i] = get_l_pix(e->tab_three[i], e->tab_light, e->l_obj, flag);
		i++;
		flag = 1;
	}
}

t_color2				get_pixel(t_three *branch, t_color2 pixel, t_env_cl *e, char flag, double coef_t)
{
	t_color2			color_ray;
	static int			i = 0;

	flag ? (i = 0) : 0;
	if (!branch)
		return ((t_color2){0, 0, 0, 0});
	if (branch->r_reflec)
	{
		color_ray = get_pixel(branch->r_reflec, pixel, e, 0, coef_t);
		color_ray = mult_color(color_ray, branch->p_hit.coef * e->l_obj[branch->id].ind_reflec);
		pixel = add_color(pixel, color_ray);
	}
	if (branch->r_refrac)
	{
		color_ray = get_pixel(branch->r_refrac, pixel, e, 0, coef_t);
		color_ray = mult_color(color_ray, branch->p_hit.coef * e->l_obj[branch->id].ind_transp * (1 - e->l_obj[branch->id].ind_reflec));
		color_ray.r = color_ray.r * (1 - branch->c_origin.r / 255.0);
		color_ray.g = color_ray.g * (1 - branch->c_origin.g / 255.0);
		color_ray.b = color_ray.b * (1 - branch->c_origin.b / 255.0);
		pixel = add_color(pixel, color_ray);
	}
	if (branch->p_hit.coef * (1 - e->l_obj[branch->id].ind_transp) * (1 - e->l_obj[branch->id].ind_reflec) > 0.04)
	{
		color_ray = mult_color((t_color2){(unsigned char)e->color_lst[i].r, (unsigned char)e->color_lst[i].g, (unsigned char)e->color_lst[i].b, 0}, branch->p_hit.coef * (1 - e->l_obj[branch->id].ind_transp) * (1 - e->l_obj[branch->id].ind_reflec) / coef_t);
		pixel = add_color(pixel, color_ray);
		i++;
	}
	return (pixel);
}

void                get_image(t_env *e)
{
	int				i;
	int				tx;
	int				ty;
	int				tmpx;
	int				tmpy;
	t_color2		pixel;
	char			flag;
	unsigned char 	*img;
	int				color[3];

	flag = 1;
	i = 0;
	img = malloc(e->mlx->h * e->mlx->w * 4);
	while (i < e->mlx->h * e->mlx->w)
	{
		pixel = get_pixel(e->tab_three[i], (t_color2){0, 0, 0, 0}, e->cl_e, flag, e->coef_t[i]);
		img[i * 4 + 2] = pixel.r;
		img[i * 4 + 1] = pixel.g;
		img[i * 4 + 0] = pixel.b;
		i++;
		flag = 0;
	}
	i = 0;
	tx = 0;
	ty = 0;
	while (i < e->mlx->h * e->mlx->w / e->anti_a / e->anti_a)
	{
		tmpy = 0;
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
		while (tmpy < e->anti_a)
		{
			tmpx = 0;
			while (tmpx < e->anti_a)
			{
				color[0] += img[tx * 4 + ty * e->mlx->w * 4 + 2 + tmpy * e->mlx->w * 4 + tmpx * 4];
				color[1] += img[tx * 4 + ty * e->mlx->w * 4 + 1 + tmpy * e->mlx->w * 4 + tmpx * 4];
				color[2] += img[tx * 4 + ty * e->mlx->w * 4 + 0 + tmpy * e->mlx->w * 4 + tmpx * 4];
				tmpx++;
			}
			tmpy++;
		}
		e->mlx->data[i * 4 + 0] = color[2] / e->anti_a / e->anti_a;
		e->mlx->data[i * 4 + 1] = color[1] / e->anti_a / e->anti_a;
		e->mlx->data[i * 4 + 2] = color[0] / e->anti_a / e->anti_a;
		i++;
		tx = (tx + e->anti_a) % e->mlx->w;
		tx == 0 ? ty += e->anti_a : 0;
	}
}

void				*ft_launch(void *env)
{
	t_env 		*tab_env;
	t_env 		*e;
	int			i;
	long int	size[3];
	pthread_t	tab_thread[3];
	// double		coef[((t_env*)env)->mlx->h * ((t_env*)env)->mlx->w];

	printf("Ft_lauch execution\n");
	e = (t_env *)env;
	// e->coef_t = coef;
	e->coef_t = malloc(sizeof(double) * e->mlx->w * e->mlx->h);
	e->actual_indice = 1;
	if (!(e->tab_three = (t_three **)malloc(sizeof(t_three *) * e->mlx->w * e->mlx->h)))
		ft_error(MALLOC, "ft_launch");
	e->default_indice = 1;
	size[0] = 0;
	size[1] = 0;
	size[2] = 0;
	i = 0;
	// while (i < e->nb_obj)
	// {
	// 	printf("%d %d %d id = %d\n", e->l_obj[i].color.r, e->l_obj[i].color.g, e->l_obj[i].color.b, e->l_obj[i].id);
	// 	i++;
	// }
	e->nb_obj_pix[0] = &(size[0]);
	e->nb_obj_pix[1] = &(size[1]);
	e->nb_obj_pix[2] = &(size[2]);
	printf("creation arbre\n");
	tab_env = ft_create_tab_env(*e);
	printf("Appelle de la premier thread!\n");
	pthread_create(&tab_thread[0], NULL, boucle, (void *)(&tab_env[0]));
	printf("Appelle de la deuxieme thread!\n");
	pthread_create(&tab_thread[1], NULL, boucle, (void *)(&tab_env[1]));
	printf("Appelle de la troisieme thread!\n");
	pthread_create(&tab_thread[2], NULL, boucle, (void *)(&tab_env[2]));
	printf("Fin des thread\n");
	i = 0;
	while (i < 3)
	{
		printf("J'attends!\n");
		pthread_join(tab_thread[i], NULL);
		i++;
	}
	size[0] = *(e->nb_obj_pix[0]) + *(e->nb_obj_pix[1]) + *(e->nb_obj_pix[2]);
	if (!(e->tab_light = (t_l_obj *)malloc(sizeof(t_l_obj) * size[0])))
		ft_error(MALLOC, "ft_launch");
	printf("creation tab_light\n");
	if (size[0] > 0)
	{
		get_l_tab(e);
		printf("Get l_tfinish\n");
		printf("start_GPU\n");
		ft_launch_calc(e, e->cl_e->cl);
		printf("apply add_light\n");
		get_image(e);
		printf("Get image finish\n");
		printf("Start filter\n");
		e->filter_t != NULL ? e->filter_t(e, 0, 0) : 0;
		printf("filter finish\n");
		mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
		mlx_do_sync(e->mlx->mlx);
		printf("affiche\n");
	}
	i = 0;
	while (i < e->mlx->h * e->mlx->w)
	{
		free_branch(e->tab_three[i]);
		i++;
	}
	free(e->tab_three);
	free(e->tab_light);
	printf("free finish\n");
	pthread_exit(NULL);
}

void		free_l_obj(t_obj **lst, int nb)
{
	if (nb < 1)
		return ;
	free(*lst);
}

void			ft_creat_lst_obj(t_env *e)
{
	t_parse_obj			*parse_obj_b;
	t_parse_light		*parse_light_b;
	int 				i;

	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	free_l_obj(&e->l_obj, e->nb_obj);
	i = 0;
	while (parse_obj_b)
	{
		parse_obj_b = parse_obj_b->next;
		i++;
	}
	e->nb_obj = i;
	i = 0;
	while (parse_light_b)
	{
		parse_light_b = parse_light_b->next;
		i++;
	}
	e->nb_light = i;
	if (!(e->l_obj = (t_obj *)malloc(sizeof(t_obj) * e->nb_obj)))
		ft_error(MALLOC, "e->l_obj -> rt.h");
	if (!(e->light = (t_light *)malloc(sizeof(t_light) * e->nb_light)))
		ft_error(MALLOC, "e->light -> rt.h");
	parse_obj_b = e->parse_obj;
	parse_light_b = e->parse_light;
	i = 0;
	while (parse_obj_b)
	{
		e->l_obj[i] = parse_obj_b->obj;
		e->l_obj[i].id = i;
		parse_obj_b = parse_obj_b->next;
		i++;
	}
	i = 0;
	while (parse_light_b)
	{
		e->light[i] = parse_light_b->light;
		parse_light_b = parse_light_b->next;
		i++;
	}
}

// void			free_env(t_env *e)
// {
// 	free(e->l_obj);
// 	free(e->light);
// 	free(e->cam);
// 	free(e->cl_e->cl);
// 	free(e->mlx);
// }

// void			ft_affiche_textures(t_env *e)
// {
// 	int x;

// 	x = 0;
// 	while (e->path_tex[x])
// 	{
// 		printf("e->path_tex: %s\n", e->path_tex[x]);
// 		x++;
// 	}
// 	x = 0;
// 	while (x < e->nb_obj)
// 	{
// 		printf("obj %d a pour texture %d\n", x, e->l_obj[x].id_texture);
// 		x++;
// 	}
// }

void			ft_get_image_texture(t_env *e)
{
	int			x;
	char		*path;
	struct stat	test;

	x = 0;
	while (e->path_tex[x])
		x++;
	e->nb_tex = x;
	e->texture = malloc(sizeof(t_mlx) * x);
	x = 0;
	while (e->path_tex[x])
	{
		path = ft_strjoin("./", e->path_tex[x]);
		if (stat(path, &test) == -1)
			ft_error("File texture doesn't exist : ", path);
		if (!(e->texture[x].img = mlx_xpm_file_to_image(e->mlx->mlx, path, &e->texture[x].w, &e->texture[x].h)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->img");
		if (!(e->texture[x].data = mlx_get_data_addr(e->texture[x].img,
			&e->texture[x].bpp, &e->texture[x].sizeline, &e->texture[x].endian)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->data");
		// if (x == 2)
		// {
		// 	int y;

		// 	y = 0;
		// 	printf("size = %d %d\n", e->texture[x].w, e->texture[x].h);
		// 	while (y < e->texture[x].w * e->texture[x].h)
		// 	{
		// 		printf("%d ", e->texture[x].data[y]);
		// 		y++;
		// 	}
		// 	free(path);
		// }
		x++;
	}
}


void			parse_file(char *name , t_env *e)
{
	int		len_name;

	len_name = ft_strlen(name);
	e->parse_light = NULL;
	e->parse_obj = NULL;

	if (!ft_strcmp(name + (len_name - 3), ".rt"))
		ft_parse(name, e);
	else if (!ft_strcmp(name + (len_name - 5), ".json"))
		ft_parse_j(name, e);
	//else if (!ft_strcmp(name + (len_name - 4), ".obj"))
	//	ft_parse_obj_files1(name, e);
	ft_creat_lst_obj(e);
	e->flag = 0;
}

int				main(int ac, char **av)
{
	t_env		e;
	e.anti_a = 1;
	init(&e);
	e.anti_a = 1;
	e.path_tex = malloc(sizeof(char *));
	e.path_tex[0] = NULL;
	if (ac == 2)
		parse_file(av[1] , &e);

	ft_init_opencl(&e, e.cl_e->cl);
	// ft_affiche_textures(&e);
	graphic_interface(&e);
	return (1);
}
