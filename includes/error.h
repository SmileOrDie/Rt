/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:24:22 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/19 17:12:17 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>
# include <unistd.h>

# define NUMBER_ARG "number of argument not right :"
# define FILES_E "No such file : "
# define MALLOC "failed function malloc in :"
# define ARG_N "argument can't be -NULL- in :"
# define MLX "mlx failed :"

void		ft_error(char *error, char *in);

#endif
