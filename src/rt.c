/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:31:39 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/22 19:32:19 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

t_env				*ft_create_tab_env(t_env e, int i)
{
	t_env	*tab;

	tab = (t_env *)malloc(sizeof(t_env) * i);
	while (i--)
	{
		tab[i] = e;
		tab[i].start = i;
	}
	return (tab);
}

double				get_l_pix(t_three *branch, t_l_obj *tab_light,
	t_obj *l_obj, char flag)
{
	static long int	i = 0;
	static double	coef_t = 0;

	flag == 2 ? (i = 0) : 0;
	flag ? (coef_t = 0) : 0;
	if (branch && branch->id < 0)
	{
		get_l_pix(branch->r_refrac, tab_light, l_obj, 0);
		return (coef_t);
	}
	if (branch && branch->r_reflec)
		get_l_pix(branch->r_reflec, tab_light, l_obj, 0);
	if (branch && branch->r_refrac)
		get_l_pix(branch->r_refrac, tab_light, l_obj, 0);
	if (branch && branch->id > 0 && branch->p_hit.coef * (1 - l_obj[branch->id - 1].ind_transp) * (1 - l_obj[branch->id - 1].ind_reflec) > 0.039)
	{
		tab_light[i].id = branch->id - 1;
		tab_light[i].p_hit_x = branch->p_hit.x;
		tab_light[i].p_hit_y = branch->p_hit.y;
		tab_light[i].p_hit_z = branch->p_hit.z;
		coef_t += branch->p_hit.coef * (1 - l_obj[branch->id - 1].ind_transp) * (1 - l_obj[branch->id - 1].ind_reflec);
		i++;
	}
	return (coef_t);
}

void				*run_rt(void *env)
{
	int			y;
	int			x;
	t_vector	p_cam;
	t_vector	v_ray;
	t_env		*e;
	double		opti[6];

	e = (t_env *)env;
	opti[0] = e->cam.u.x * (e->cam.w / e->win.w);
	opti[1] = e->cam.up.x * (e->cam.h / e->win.h);
	opti[2] = e->cam.u.y * (e->cam.w / e->win.w);
	opti[3] = e->cam.up.y * (e->cam.h / e->win.h);
	opti[4] = e->cam.u.z * (e->cam.w / e->win.w);
	opti[5] = e->cam.up.z * (e->cam.h / e->win.h);
	y = 0;
	while (y < e->win.h)
	{
		x = e->start;
		while (x < e->win.w)
		{
			p_cam = new_v(e->cam.l.x + opti[0] * (double)x + opti[1] * (double)y, e->cam.l.y + opti[2] * (double)x + opti[3] * (double)y, e->cam.l.z + opti[4] * (double)x + opti[5] * (double)y);
			v_ray = vsub(p_cam, e->cam.eye);
			vnorm(&v_ray);
			e->begin_three = &(e->tab_three[x + y * e->win.w]);
			ft_raytracer(e, e->cam.eye, v_ray, 0, 1, (t_color2){255, 255, 255, 0}, &(e->tab_three[x + y * e->win.w]));
			x += 8;
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
	while (i < e->win.h * e->win.w)
	{
		e->coef_t[i] = get_l_pix(e->tab_three[i], e->tab_light, e->l_obj, flag);
		i++;
		flag = 1;
	}
}

t_color2			get_pixel(t_three *branch, t_color2 pixel, t_env_cl *e, char flag, double coef_t)
{
	t_color2		color_ray;
	static int		i = 0;

	flag ? (i = 0) : 0;
	if (!branch)
		return ((t_color2){0, 0, 0, 0});
	if (branch->id < 0)
	{
		color_ray = get_pixel(branch->r_refrac, pixel, e, 0, coef_t);
		pixel = add_color(pixel, color_ray);
		return (pixel);
	}
	if (branch->r_reflec)
	{
		color_ray = get_pixel(branch->r_reflec, pixel, e, 0, coef_t);
		color_ray = mult_color(color_ray, branch->p_hit.coef * e->l_obj[branch->id - 1].ind_reflec);
		pixel = add_color(pixel, color_ray);
	}
	if (branch->r_refrac)
	{
		color_ray = get_pixel(branch->r_refrac, pixel, e, 0, coef_t);
		color_ray.r = color_ray.r * (branch->c_origin.r / 255.0);
		color_ray.g = color_ray.g * (branch->c_origin.g / 255.0);
		color_ray.b = color_ray.b * (branch->c_origin.b / 255.0);
		color_ray = mult_color(color_ray, branch->p_hit.coef * e->l_obj[branch->id - 1].ind_transp * (1 - e->l_obj[branch->id - 1].ind_reflec));
		pixel = add_color(pixel, color_ray);
	}
	if (branch->p_hit.coef * (1 - e->l_obj[branch->id - 1].ind_transp) * (1 - e->l_obj[branch->id - 1].ind_reflec) > 0.039)
	{
		color_ray = e->l_obj[branch->id - 1].negatif > 0 ? mult_color((t_color2){(unsigned char)e->color_lst[i].r, (unsigned char)e->color_lst[i].g, (unsigned char)e->color_lst[i].b, 0}, branch->p_hit.coef / coef_t) : mult_color((t_color2){(unsigned char)e->color_lst[i].r, (unsigned char)e->color_lst[i].g, (unsigned char)e->color_lst[i].b, 0}, branch->p_hit.coef * (1 - e->l_obj[branch->id - 1].ind_transp) * (1 - e->l_obj[branch->id - 1].ind_reflec) / coef_t);
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
	int				opti[4];

	flag = 1;
	i = 0;
	opti[0] = e->win.h * e->win.w;
	opti[1] = e->anti_a * e->anti_a;
	opti[2] = opti[0] / opti[1];
	img = malloc(opti[0] * 4);
	while (i < opti[0])
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
	while (i < opti[2])
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
				opti[3] = tx * 4 + ty * e->win.w * 4 + tmpy * e->win.w * 4 + tmpx * 4;
				color[0] += img[opti[3] + 2];
				color[1] += img[opti[3] + 1];
				color[2] += img[opti[3] + 0];
				tmpx++;
			}
			tmpy++;
		}
		e->mlx.data[i * 4 + 0] = color[2] / opti[1];
		e->mlx.data[i * 4 + 1] = color[1] / opti[1];
		e->mlx.data[i * 4 + 2] = color[0] / opti[1];
		i++;
		tx = (tx + e->anti_a) % e->win.w;
		tx == 0 ? ty += e->anti_a : 0;
	}
	free(img);
}

static void			mlx_put_load(t_env *e, int i)
{
	t_pos l;

	l = (t_pos){e->win.w / e->anti_a , e->win.h / e->anti_a};
	if (e->wait == 0 || !e->mlx.mlx || !e->mlx.win || !e->wait_img[i] ||
		!(e->size[i].w <= l.w && e->size[i].h <= l.h))
		return ;
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->wait_img[i],
		(l.w / 2) - (e->size[i].w / 2), (l.h / 2) - (e->size[i].h / 2));
}

static long int		ft_launch_thread(t_env *e)
{
	t_env 			*tab_env;
	long int		size_f;
	pthread_t		tab_thread[8];
	int				i;

	i = 8;
	tab_env = ft_create_tab_env(*e, i);
	while (i--)
		pthread_create(&tab_thread[i], NULL, run_rt, (void *)(&tab_env[i]));
	size_f = 0;
	while (++i < 8)
	{
		pthread_join(tab_thread[i], NULL);
		size_f += *(e->nb_obj_pix[i]);
	}
	if (!(e->tab_light = (t_l_obj *)malloc(sizeof(t_l_obj) * size_f)))
		ft_error(MALLOC, "ft_launch");
	return (size_f);
}

static void			ft_launch_after(t_env *e)
{
	mlx_put_load(e, 1);
	get_l_tab(e);
	mlx_put_load(e, 2);
	ft_launch_calc(e, e->cl_e->cl);
	mlx_put_load(e, 3);
	get_image(e);
	e->filter_t != NULL ? e->filter_t(e, 0, 0) : 0;
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
}

static void			ft_launch_free(t_env *e, unsigned int limit)
{
	unsigned int	i;

	i = 0;
	while (i < limit)
		free_branch(e->tab_three[i++]);
	free(e->tab_three);
	free(e->tab_light);
	e->b_screen = 0;
	e->flag = 0;
}

void				*ft_launch(void *env)
{
	t_env 			*e;
	unsigned int	l;
	long int		size[8];
	int				i;

	e = (t_env *)env;
	printf("%f\n", e->amb);
	i = -1;
	while (++i < 8)
	{
		size[i] = 0;
		e->nb_obj_pix[i] = &(size[i]);
	}
	l = e->win.w * e->win.h;
	if (!(e->coef_t = (double*)malloc(sizeof(double) * l)))
		ft_error(MALLOC, "e->coef_t => ft_launch");
	if (!(e->tab_three = (t_three **)malloc(sizeof(t_three *) * l)))
		ft_error(MALLOC, "e->tab_three => ft_launch");
	mlx_put_load(e, 0);
	if ((size[0] = ft_launch_thread(e)) > 0)
		ft_launch_after(e);
	ft_launch_free(e, l);
	return (NULL);
}

void 				all_texture(t_envg *e, char *path, int x)
{
	SDL_Surface *surface;
	int len;

	len = (ft_strlen(path) - 4);
	if (ft_strcmp(path + len, ".xpm") == 0 || ft_strcmp(path + len, ".XPM") == 0)
	{
		if (!(e->e->texture[x].img = mlx_xpm_file_to_image(e->mlx.mlx, path, &e->e->texture[x].w, &e->e->texture[x].h)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->img");
		if (!(e->e->texture[x].data = mlx_get_data_addr(e->e->texture[x].img,
			&e->e->texture[x].bpp, &e->e->texture[x].sizeline, &e->e->texture[x].endian)))
			ft_error(MALLOC, "xpm_file.c => void get_img(...) img->data");
	}
	else 
	{
		surface = IMG_Load(path);
		if (surface)
		{
			e->e->texture[x].data = (char *)(surface->pixels);
			e->e->texture[x].h = surface->h;
			e->e->texture[x].w = surface->w;
		}
		else 
			ft_error("SDL2 : ", ft_strjoin("IMG_Load(...) -> failed : ", SDL_GetError()));
	}
}

void				ft_get_image_texture(t_envg *e)
{
	int			x;
	char		*path;
	struct stat	test;

	x = 0;
	while (e->path_tex && e->path_tex[x])
		x++;
	e->nb_tex = x;
	e->e->texture = malloc(sizeof(t_mlx) * x);
	x = 0;
	while (e->path_tex && e->path_tex[x])
	{
		path = ft_strjoin("./", e->path_tex[x]);
		if (stat(path, &test) == -1)
			ft_error("File texture doesn't exist : ", path);
		all_texture(e, e->path_tex[x], x);
		x++;
	}
}

void				parse_file(char *name , t_envg *e)
{
	int		len_name;

	len_name = ft_strlen(name);
	if (!ft_strcmp(name + (len_name - 5), ".json"))
		ft_parse_j(name, e);
	init_id(e);
}

int					main(int ac, char **av)
{
	t_envg		e;
	t_env 		env;

	e.anti_a = 1;
	e.path_tex = NULL;
	e.e = &env;
	e.nb_tex = 0;
	e.parse_light = NULL;
	e.parse_obj = NULL;
	if (ac == 2)
		parse_file(av[1] , &e);
	ft_init_opencl(&e, e.cl_e->cl);
	graphic_interface(&e);
	return (1);
}
