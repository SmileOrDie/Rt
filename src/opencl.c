#include "../includes/rtv1.h"

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

void	ft_init_opencl(t_env *e, t_opencl *cl, int nb_source, t_env *tab_env)
{
	int		err;
	char	*source[nb_source];
	char	*namefile[nb_source];
	int		i;

	// (void)tab_env;
	err = clGetPlatformIDs(1, &cl->platform, NULL);
	err = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_ALL, 1, &cl->device, NULL);
	cl->context = clCreateContext(0, 1, &cl->device, NULL, NULL, &err);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	namefile[0] = "src_cl/rt_h.cl";
	namefile[1] = "src_cl/put_pixel.cl";
	namefile[2] = "src_cl/inter_object.cl";
	namefile[3] = "src_cl/angle_object.cl";
	namefile[4] = "src_cl/raytrace.cl";
	namefile[5] = "src_cl/rt.cl";
	namefile[6] = "src_cl/vector.cl";
	i = 0;
	while (i < nb_source)
	{
		source[i] = ft_create_source(namefile[i]);
		i++;
	}
	cl->kernel_program = clCreateProgramWithSource(cl->context, nb_source, (const char **)source, 0, &err);
	err = clBuildProgram(cl->kernel_program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		size_t	len;
		char	buffer[100000];

		printf("Error: Failed to build program executable!\n");
		err = clGetProgramBuildInfo(cl->kernel_program, cl->device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
		exit(1);
	}
	// printf("test : %i\n", tab_env[404].nb_obj);
	cl->kernel = clCreateKernel(cl->kernel_program, "ft_start_calc", &err);
	cl->data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(char) * 4 * e->mlx->w * e->mlx->h, NULL, &err);
	cl->obj = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * e->nb_obj, e->l_obj, &err);
	cl->light = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_light) * e->nb_light, e->light, &err);
	cl->env = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_env) * e->mlx->h, tab_env, &err);
	cl->mlx = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_mlx), e->mlx, &err);
	cl->cam = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_cam), e->cam, &err);
}

void	ft_launch_calc(t_env *e, t_opencl *cl)
{
	size_t	global[1];
	int		err;

	// printf("test\n");
	if (e->move == 1)
	{
		clReleaseMemObject(cl->cam);
		cl->cam = clCreateBuffer(cl->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_cam), e->cam, &err);
		e->move = 0;
	}
	err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&cl->data);
	err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), (void *)&cl->obj);
	err = clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), (void *)&cl->light);
	err = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), (void *)&cl->env);
	err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), (void *)&cl->mlx);
	err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), (void *)&cl->cam);
	global[0] = e->mlx->h;
	err = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0, global, 0, 0, 0, 0);
	err = clEnqueueReadBuffer(cl->command_queue, cl->data, CL_TRUE, 0, sizeof(char) * 4 * e->mlx->w * e->mlx->h, e->mlx->data, 0, NULL, NULL);
	// printf("end\n");
	// exit(0);
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
}