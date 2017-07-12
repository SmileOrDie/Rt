/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:18:07 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/12 17:27:31 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORME_H
# define NORME_H

# include "../libft/includes/libft.h"
# include "../vector/includes/vector.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <OpenCL/opencl.h>
# include <sys/stat.h>
# include <string.h>
# include <math.h>
# include <pthread.h>
# include "../includes/interface_rt.h"

typedef struct				s_norme1
{
	double					alpha;
	t_vector				origin;
	t_vector				tmp1;
	t_vector				tmp2;
	t_vector				dir_dir;
	t_vector				o_dir;
	double					ret;
}							t_norme1;

#endif
