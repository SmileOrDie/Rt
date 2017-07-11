/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/11 14:37:44 by pde-maul         ###   ########.fr       */
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
// <<<<<<< HEAD
// 	cl->env = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | \
// 		CL_MEM_COPY_HOST_PTR, sizeof(t_env_cl), e->cl_e, &n.err);
// 	n.err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e -> ",\
// 	ft_itoa(n.err))) : 0;
// 	ft_launch_calc2(e, cl, n);
// =======
	// printf("14\n");
	(n.err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), (void *)&cl->texture)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 0 -> ", ft_itoa(n.err))) : 0;
	// printf("15\n");
	(n.err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), (void *)&cl->lst)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 0 -> ", ft_itoa(n.err))) : 0;
	// printf("16\n");
	(n.err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), (void *)&cl->obj)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 1 -> ", ft_itoa(n.err))) : 0;
	// printf("17\n");
	(n.err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), (void *)&cl->light)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 2 -> ", ft_itoa(n.err))) : 0;
	// printf("18\n");
	(n.err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), (void *)&cl->env)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 3 -> ", ft_itoa(n.err))) : 0;
	// printf("19\n");
	(n.err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&cl->color_lst)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 4 -> ", ft_itoa(n.err))) : 0;
	// err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), (void *)&cl->mlx);
	// err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), (void *)&cl->cam);
	// err = clSetKernelArg(cl->kernel, 6, sizeof(cl_int), (void *)&i);
	// global[1] = e->mlx->h / 2;
	// printf("%d\n", err);
	// printf("20\n");
	n.global[0] = *(e->nb_obj_pix[0]);
	// global[1] = 3;
	// global[1] = e->mlx->w;
	// printf("%d\n", e->cl_e->lst[0].id);
	// printf("%d\n", e->cl_e->lst[1].id);
	// printf("%d\n", e->cl_e->lst[2].id);
	// printf("light.r = %d\n", (e->light)[1].color.r);
	// printf("light.g = %d\n", (e->light)[1].color.g);
	// printf("light.b = %d\n", (e->light)[1].color.b);
	// printf("21\n");
	(n.err = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0, n.global, 0, 0, 0, 0)) ? ft_error(KERNEL, ft_strjoin("clEnqueueNDRangeKernel", ft_itoa(n.err))) : 0;
	// printf("22\n");
	// printf(" t_obj_size%ld\n", sizeof(t_obj));
	// printf("sizeof(s_u) = %ld\n", sizeof(t_u));

	// printf(" t_env_cl_size %ld\n", sizeof(t_env_cl));
	// printf(" t_obj %ld\n", sizeof(t_obj));
	// printf(" t_l_obj %ld\n", sizeof(t_l_obj));
	// printf(" t_light %ld\n", sizeof(t_light));
	// printf(" t_vector %ld\n", sizeof(t_vector));
	// printf(" t_color2 %ld\n", sizeof(t_color2));
	// printf(" char* %ld\n", sizeof(char *));
	// printf(" Total %ld\n\n", sizeof(char *) + sizeof(int) * 2 + sizeof(t_vector) * 3 + sizeof(double) * 5 + sizeof(t_color2));

	// printf("vacuum = %ld\n", e->cl_e->vacuum);

	// i = 0;
	(n.err = clEnqueueReadBuffer(cl->command_queue, cl->color_lst, CL_TRUE, 0, sizeof(t_color2) * *(e->nb_obj_pix[0]), e->cl_e->color_lst, 0, NULL, NULL)) ? ft_error(KERNEL, ft_strjoin("clEnqueueReadBuffer", ft_itoa(n.err))) : 0;
	// printf("23\n");
	// clReleaseKernel(cl->kernel);
	// clReleaseProgram(cl->kernel_program);
	// clReleaseCommandQueue(cl->command_queue);
	clReleaseMemObject(cl->obj);
	clReleaseMemObject(cl->light);
	clReleaseMemObject(cl->env);
	clReleaseMemObject(cl->color_lst);
	// clReleaseContext(cl->context);
// 	// exit(0);;

// }
	// printf("end\n");

	// printf("%ld\n", sizeof(t_env_cl));
	// printf("finished\n");
	// err = clEnqueueReadBuffer(cl->command_queue, cl->data, CL_TRUE, 0, sizeof(char) * e->mlx->w * e->mlx->h, e->mlx->data + 0 * e->mlx->w * e->mlx->h, 0, NULL, NULL);
	// i = 1;
	// err = clEnqueueReadBuffer(cl->command_queue, cl->data, CL_TRUE, 0, sizeof(char) * e->mlx->w * e->mlx->h, e->mlx->data + 1 * e->mlx->w * e->mlx->h, 0, NULL, NULL);
	// i = 2;
	// err = clEnqueueReadBuffer(cl->command_queue, cl->data, CL_TRUE, 0, sizeof(char) * e->mlx->w * e->mlx->h, e->mlx->data + 2 * e->mlx->w * e->mlx->h, 0, NULL, NULL);
	// i = 3;
	// err = clEnqueueReadBuffer(cl->command_queue, cl->data, CL_TRUE, 0, sizeof(char) * e->mlx->w * e->mlx->h, e->mlx->data + 3 * e->mlx->w * e->mlx->h, 0, NULL, NULL);
	// printf("end\n");
	// exit(0);
	// int x = 0;
	// while (x < e->mlx->h * 4 * e->mlx->w)
	// {
	// 	if ((unsigned char)(e->mlx->data)[x + 2] == 254 && (unsigned char)(e->mlx->data)[x + 1] == 0 && (unsigned char)(e->mlx->data)[x] == 0)
	// 	{
	// 		printf("r = %d, g = %d, b = %d\n", (unsigned char)(e->mlx->data)[x], (unsigned char)(e->mlx->data)[x + 1], (unsigned char)(e->mlx->data)[x + 2]);
	// 		printf("x = %d et y = %d\n", x % (e->mlx->h * 4), x / (e->mlx->h * 4));
	// 	}
	// 	x += 4;
	// }
	// if (e->mlx->mlx && e->mlx->win && e->mlx->img)
	// 	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
// >>>>>>> master
}
