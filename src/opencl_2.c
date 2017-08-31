/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/08/30 14:46:04 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void		ft_launch_releasemem(t_opencl *cl)
{
	clReleaseMemObject(cl->obj);
	clReleaseMemObject(cl->light);
	clReleaseMemObject(cl->env);
	clReleaseMemObject(cl->color_lst);
	clReleaseMemObject(cl->lst);
	clReleaseMemObject(cl->texture);
}

static void		ft_l_clsetkernelarg(t_opencl *cl, int err)
{
	(err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem),
		(void *)&cl->color_lst)) ? ft_l_err(err, 0) : 0;
	(err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem),
		(void *)&cl->obj)) ? ft_l_err(err, 1) : 0;
	(err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem),
		(void *)&cl->light)) ? ft_l_err(err, 2) : 0;
	(err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem),
		(void *)&cl->env)) ? ft_l_err(err, 3) : 0;
	(err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem),
		(void *)&cl->lst)) ? ft_l_err(err, 4) : 0;
	(err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem),
		(void *)&cl->texture)) ? ft_l_err(err, 5) : 0;
}

static void		ft_l_clcreatebuffer_2(t_env *e, t_opencl *cl, int err)
{
	cl->env = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, sizeof(t_env_cl), e->cl_e, &err);
	err ? ft_l_err(err, 11) : 0;
	cl->lst = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, sizeof(t_l_obj) * *(e->nb_obj_pix[0]),
		e->cl_e->lst, &err);
	err ? ft_l_err(err, 12) : 0;
	cl->color_lst = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, sizeof(t_color2) * *(e->nb_obj_pix[0]),
		e->cl_e->color_lst, &err);
	err ? ft_l_err(err, 13) : 0;
}

static void		ft_l_clcreatebuffer(t_env *e, t_opencl *cl, int err)
{
	cl->obj = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * e->nb_obj, e->l_obj, &err);
	err ? ft_l_err(err, 9) : 0;
	cl->light = NULL;
	if (e->nb_light > 0)
	{
		cl->light = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, sizeof(t_light) * e->nb_light, e->light, &err);
		err ? ft_l_err(err, 10) : 0;
	}
	cl->texture = NULL;
	if (e->nb_tex > 0)
	{
		cl->texture = clCreateBuffer(cl->context, CL_MEM_READ_WRITE |
			CL_MEM_COPY_HOST_PTR, sizeof(t_mlx) * e->nb_tex, e->texture, &err);
		err ? ft_l_err(err, 14) : 0;
	}
	ft_l_clcreatebuffer_2(e, cl, err);
}

void			ft_launch_calc(t_env *e, t_opencl *cl)
{
	size_t	global[1];
	int		err;

	err = 0;
	init_cl_e(e, e->cl_e);
	ft_l_clcreatebuffer(e, cl, err);
	ft_l_clsetkernelarg(cl, err);
	global[0] = *(e->nb_obj_pix[0]);
	(err = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0, global,
		0, 0, 0, 0)) ? ft_l_err(err, 6) : 0;
	(err = clEnqueueReadBuffer(cl->command_queue, cl->color_lst, CL_TRUE, 0,
		sizeof(t_color2) * *(e->nb_obj_pix[0]), e->cl_e->color_lst, 0, NULL,
		NULL)) ? ft_l_err(err, 7) : 0;
	ft_launch_releasemem(cl);
}
