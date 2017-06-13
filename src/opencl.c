/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/10 16:25:59 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

char	*ft_create_source(char *file_name)
{
	int fd;
	unsigned int file_len;
	struct stat file_status;
	char *source;

	fd = open(file_name, O_RDONLY);
	fstat(fd, &file_status);
	file_len = file_status.st_size;
	source = (char *)malloc(sizeof(char) * (file_len + 1));
	read(fd, source, file_len);
	close(fd);
	source[file_len] = 0;
	return (source);
}

void	init_cl_e(t_env *e, t_env_cl *cl)
{
	cl->lst = e->tab_light;
	cl->light = e->light;
	cl->l_obj = e->l_obj;
	cl->nb_obj = e->nb_obj;
	cl->nb_light = e->nb_light;
	if (!(cl->color_lst = (t_color2 *)malloc(sizeof(t_color2) * *(e->nb_obj_pix[0]))))
		ft_error(MALLOC, "init_cl_e");
}

// void	start_cl(t_env *e, t_opencl *cl)
// {
// 	int err;


// 	// cl->data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(char) * 4 * e->mlx->w * e->mlx->h, NULL, &err);


// 	// cl->mlx = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_mlx), e->mlx, &err);
// 	// cl->cam = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_cam), e->cam, &err);
// 	// cl->lst = clCreateBuffer(cl->context, CL_MEM_READ_ONLY, sizeof(t_l_obj) * *(e->nb_obj_pix[0]), NULL, &err);
// 	// printf("Error 13 :%d\n", err);
// 	// err = clEnqueueWriteBuffer(cl->command_ queue, cl->lst, true, 0, sizeof(t_l_obj) * *(e->nb_obj_pix[0]), e->cl_e->lst, 0, NULL, NULL);
// 	// printf("Error 14 :%d\n", err);
// }

void	ft_init_opencl(t_env *e, t_opencl *cl)
{
	int		err;
	char	*source[5];
	char	*namefile[5];
	int		i;
	size_t	len;
	char	buffer[100000];

	err = clGetPlatformIDs(1, &cl->platform, NULL);
	err = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_ALL, 1, &cl->device, NULL);
	cl->context = clCreateContext(0, 1, &cl->device, NULL, NULL, &err);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	namefile[0] = "src_cl/rt_h.cl";
	namefile[1] = "src_cl/add_light.cl";
	namefile[2] = "src_cl/inter_object.cl";
	namefile[3] = "src_cl/angle_object.cl";
	namefile[4] = "src_cl/vector.cl";
	i = 0;
	while (i < 5)
	{
		source[i] = ft_create_source(namefile[i]);
		i++;
	}
	cl->kernel_program = clCreateProgramWithSource(cl->context, 5, (const char **)source, 0, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateProgramWithSource -> cl->kernel_program -> ", ft_itoa(err))) : 0;
	if ((err = clBuildProgram(cl->kernel_program, 0, NULL, NULL, NULL, NULL)) != CL_SUCCESS)
	{
		(err = clGetProgramBuildInfo(cl->kernel_program, cl->device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len)) ? ft_error(KERNEL, ft_strjoin("clGetProgramBuildInfo -> cl->kernel_program -> ", ft_itoa(err))) : 0;
		ft_putendl_fd(buffer, 2);
		exit(1);
	}
	e->cl_e->cl = cl;
	i = 0;
	while (i < 5)
	{
		free(source[i]);
		i++;
	}
}

typedef struct	s_u
{
}				t_u;

void	ft_launch_calc(t_env *e, t_opencl *cl)
{
	size_t	global[1];
	int		err;
	// cl_int	i;

	// if (e->move == 1)
	// {
	// 	if (cl->cam)
			// clReleaseMemObject(cl->cam);
		// cl->cam = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_cam), e->cam, &err);
	// 	e->move = 0;
	// e->cl_e->vacuum = *(e->nb_obj_pix[0]);
	// }
	// err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&cl->data);
	init_cl_e(e, e->cl_e);
	cl->kernel = clCreateKernel(cl->kernel_program, "ft_start_calc", &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateKernel -> cl->kernel -> ", ft_itoa(err))) : 0;
	// printf("e->l_obj[3].color.b = %d\n", e->l_obj[3].color.b);
	// printf("%lu\n", sizeof(t_obj));
	cl->obj = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * e->nb_obj, e->l_obj, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->l_obj -> ", ft_itoa(err))) : 0;
	if (e->nb_light != 0)
	{
		cl->light = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_light) * e->nb_light, e->light, &err);
		err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e->light -> ", ft_itoa(err))) : 0;
	}
	cl->env = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_env_cl), e->cl_e, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e -> ", ft_itoa(err))) : 0;
	cl->lst = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_l_obj) * *(e->nb_obj_pix[0]), e->cl_e->lst, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e->lst -> ", ft_itoa(err))) : 0;
	cl->color_lst = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_color2) * *(e->nb_obj_pix[0]), e->cl_e->color_lst, &err);
	err ? ft_error(KERNEL, ft_strjoin("clCreateBuffer -> e->cl_e->color_lst -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), (void *)&cl->lst)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 0 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), (void *)&cl->obj)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 1 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), (void *)&cl->light)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 2 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), (void *)&cl->env)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 3 -> ", ft_itoa(err))) : 0;
	(err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&cl->color_lst)) ? ft_error(KERNEL, ft_strjoin("clSetKernelArg 4 -> ", ft_itoa(err))) : 0;
	// err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), (void *)&cl->mlx);
	// err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), (void *)&cl->cam);
	// err = clSetKernelArg(cl->kernel, 6, sizeof(cl_int), (void *)&i);
	// global[1] = e->mlx->h / 2;
	// printf("%d\n", err);
	global[0] = *(e->nb_obj_pix[0]);
	// global[1] = 3;
	// global[1] = e->mlx->w;
	// printf("%d\n", e->cl_e->lst[0].id);
	// printf("%d\n", e->cl_e->lst[1].id);
	// printf("%d\n", e->cl_e->lst[2].id);
	// printf("light.r = %d\n", (e->light)[1].color.r);
	// printf("light.g = %d\n", (e->light)[1].color.g);
	// printf("light.b = %d\n", (e->light)[1].color.b);
	(err = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0, global, 0, 0, 0, 0)) ? ft_error(KERNEL, ft_strjoin("clEnqueueNDRangeKernel", ft_itoa(err))) : 0;
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
	(err = clEnqueueReadBuffer(cl->command_queue, cl->color_lst, CL_TRUE, 0, sizeof(t_color2) * *(e->nb_obj_pix[0]), e->cl_e->color_lst, 0, NULL, NULL)) ? ft_error(KERNEL, ft_strjoin("clEnqueueReadBuffer", ft_itoa(err))) : 0;

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
}
