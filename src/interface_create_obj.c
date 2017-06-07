/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_create_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:11:19 by shamdani          #+#    #+#             */
/*   Updated: 2017/04/28 15:36:18 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static char			*ft_strjoin_2(char *str1, char *str2)
{
	char *ret;
	char *tmp;

	tmp = ft_strjoin(str1, " ");
	ret = ft_strjoin(tmp, str2);
	free(tmp);
	return (ret);
}

static void			reset_line(char **line)
{
	int i;
	int len;

	i = 0;
	while (++i <= 13)
	{
		len = ft_strlen(line[i]);
		while (len >= 0)
			line[i][len--] = '\0';
	}
}

static char 		*creat_elem3(t_envg *e, char *line)
{
	char *line_t;

	if ((ft_strcmp("sphere", e->line[1]) == 0) || (ft_strcmp("cylinder", e->line[1]) == 0) || (ft_strcmp("circle", e->line[1]) == 0))
		line_t = ft_strjoin_2(line, e->line[12]);
	else if (ft_strcmp(e->line[1], "light") == 0)
		line_t = (ft_strcmp(e->line[12], ".") == 0) ? ft_strjoin_2(line, "1") : ft_strjoin_2(line, e->line[12]);
	else if (ft_strcmp(e->line[1], "cone") == 0)
		line_t = ft_strjoin_2(line, e->line[13]);
	else
		return (line);
	free(line);
	return(line_t);
}

static char 		*creat_elem2(t_envg *e, char *line)
{
	char *line_t;

	if (!ft_strcmp("sphere", e->line[1]))
		return(line);
	if (!ft_strcmp("light", e->line[1]))
	{
		line_t = ft_strjoin_2(line, "1");
		free(line);
		return (line_t);
	}
	line_t = ft_strjoin_2(line, e->line[6]);
	free(line);
	line = ft_strjoin_2(line_t, e->line[7]);
	free(line_t);
	line_t = ft_strjoin_2(line, e->line[8]);
	free(line);
	return (line_t);
}

void				add_obj_compo(t_envg *e, char **line)
{
	char *s_tmp;
	char *s_tmp2;

	s_tmp = ft_strjoin_2(*line, e->line[13]);
	free(*line);
	s_tmp2 = ft_strjoin_2(s_tmp, e->line[14]);
	free(s_tmp);
	*line = ft_strjoin_2(s_tmp2, e->line[15]);
}

void				creat_elem(t_envg *e)
{
	char *line;
	char *line_t;

	if ((e->error = check_var_obj(e->line)) != -1)
		return ;
	line = ft_strjoin_2(e->line[1], e->line[9]);
	line_t = ft_strjoin_2(line, e->line[10]);
	free(line);
	line = ft_strjoin_2(line_t, e->line[11]);
	free(line_t);
	line_t = ft_strjoin_2(line, e->line[3]);
	free(line);
	line = ft_strjoin_2(line_t, e->line[4]);
	free(line_t);
	line_t = ft_strjoin_2(line, e->line[5]);
	free(line);
	line = creat_elem2(e, line_t);
	line_t = creat_elem3(e, line);
	if (ft_strcmp("light", e->line[1]))
		add_obj_compo(e, &line_t);
	line = ft_strjoin_2(line_t, e->line[2]);
	printf("%s\n", line);
	creat_lst(ft_strsplit(line, ' '), e->e, -1);
	free(line);
	free(line_t);
	reset_line(e->line);
}
// cam 0 150 -500 0 0 0 0 -1 0 60 150

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

