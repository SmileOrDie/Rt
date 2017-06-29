/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/29 16:58:00 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/norme.h"

void		ft_launch_calc3(t_env *e, t_opencl *cl, t_norme7 n)
{
	(n.err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), (void *)&cl->light))\
	? ft_error(KERNEL, ft_strjoin("clSetKernelArg 2 -> ", ft_itoa(n.err))) : 0;
	(n.err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), (void *)&cl->env))\
	? ft_error(KERNEL, ft_strjoin("clSetKernelArg 3 -> ", ft_itoa(n.err))) : 0;
	(n.err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), \
	(void *)&cl->color_lst)) ? ft_error(KERNEL, \
		ft_strjoin("clSetKernelArg 4 -> ", ft_itoa(n.err))) : 0;
	n.global[0] = *(e->nb_obj_pix[0]);
	(n.err = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0, \
		n.global, 0, 0, 0, 0)) ? ft_error(KERNEL, \
			ft_strjoin("clEnqueueNDRangeKernel", ft_itoa(n.err))) : 0;
	(n.err = clEnqueueReadBuffer(cl->command_queue, cl->color_lst, CL_TRUE, 0, \
		sizeof(t_color2) * *(e->nb_obj_pix[0]), e->cl_e->color_lst, 0, \
		NULL, NULL)) ? ft_error(KERNEL, ft_strjoin("clEnqueueReadBuffer", \
		ft_itoa(n.err))) : 0;
	clReleaseMemObject(cl->obj);
	clReleaseMemObject(cl->light);
	clReleaseMemObject(cl->env);
	clReleaseMemObject(cl->color_lst);
}

void		ft_launch_calc2(t_env *e, t_opencl *cl, t_norme7 n)
{
	cl->lst = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_l_obj) * *(e->nb_obj_pix[0]),\
		e->cl_e->lst, &n.err);
	n.err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e->lst -> ", \
	ft_itoa(n.err))) : 0;
	cl->color_lst = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_color2) * *(e->nb_obj_pix[0]), \
		e->cl_e->color_lst, &n.err);
	n.err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> \
	e->cl_e->color_lst -> ", ft_itoa(n.err))) : 0;
	cl->texture = NULL;
	if (e->nb_tex > 0)
	{
		cl->texture = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_mlx) * e->nb_tex, e->texture, &n.err);
		n.err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> \
		e->cl_e->texture -> ", ft_itoa(n.err))) : 0;
	}
	(n.err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), (void *)&cl->texture\
)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 0 -> ", ft_itoa(n.err))) : 0;
	(n.err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), (void *)&cl->lst)) ?\
	ft_error(KERNEL, ft_strjoin("clSetKernelArg 0 -> ", ft_itoa(n.err))) : 0;
	(n.err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), (void *)&cl->obj)) ?\
	ft_error(KERNEL, ft_strjoin("clSetKernelArg 1 -> ", ft_itoa(n.err))) : 0;
	ft_launch_calc3(e, cl, n);
}

void		ft_launch_calc(t_env *e, t_opencl *cl)
{
	t_norme7	n;

	init_cl_e(e, e->cl_e);
	cl->kernel = clCreateKernel(cl->kernel_program, "ft_start_calc", &n.err);
	n.err ? ft_error(KERNEL, ft_strjoin("clCreateKernel -> cl->kernel -> ", \
	ft_itoa(n.err))) : 0;
	cl->obj = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * e->nb_obj, e->l_obj, &n.err);
	n.err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->l_obj -> ", \
	ft_itoa(n.err))) : 0;
	cl->light = NULL;
	if (e->nb_light > 0)
	{
		cl->light = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | \
			CL_MEM_COPY_HOST_PTR, sizeof(t_light) * e->nb_light, \
			e->light, &n.err);
		n.err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> \
		e->cl_e->light -> ", ft_itoa(n.err))) : 0;
	}
	cl->env = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_env_cl), e->cl_e, &n.err);
	n.err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e -> ",\
	ft_itoa(n.err))) : 0;
	ft_launch_calc2(e, cl, n);
}
