/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:56 by pde-maul          #+#    #+#             */
/*   Updated: 2017/08/03 11:58:15 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static void	ft_l_err_2(int err, int id)
{
	if (id == 9)
		ft_error(KERNEL,
			ft_strjoin("clCreateBuffer -> e->l_obj ", ft_itoa(err)));
	else if (id == 10)
		ft_error(KERNEL,
			ft_strjoin("clCreateBuffer -> e->cl_e->light -> ",
				ft_itoa(err)));
	else if (id == 11)
		ft_error(KERNEL,
			ft_strjoin("clCreateBuffer -> e->cl_e -> ",
				ft_itoa(err)));
	else if (id == 12)
		ft_error(KERNEL,
			ft_strjoin("clCreateBuffer -> e->cl_e->lst -> ",
				ft_itoa(err)));
	else if (id == 13)
		ft_error(KERNEL,
			ft_strjoin("clCreateBuffer -> e->cl_e->color_lst -> ",
				ft_itoa(err)));
	else if (id == 14)
		ft_error(KERNEL,
			ft_strjoin("clCreateBuffer -> e->cl_e->texture -> ",
				ft_itoa(err)));
}

void		ft_l_err(int err, int id)
{
	char *error;

	if (id < 6)
	{
		error = ft_strjoin("clSetKernelArg ", ft_itoa(id));
		error = ft_strjoin(error, ft_itoa(err));
		ft_error(KERNEL, error);
	}
	else if (id == 6)
		ft_error(KERNEL, ft_strjoin("clEnqueueNDRangeKernel:", ft_itoa(err)));
	else if (id == 7)
		ft_error(KERNEL, ft_strjoin("clEnqueueReadBuffer:", ft_itoa(err)));
	else if (id == 8)
		ft_error(KERNEL, ft_strjoin("clCreateKernel cl->kernel :",
			ft_itoa(err)));
	else
		ft_l_err_2(err, id);
}
