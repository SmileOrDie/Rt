/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:54:22 by shamdani          #+#    #+#             */
/*   Updated: 2017/01/24 12:51:23 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


// static char	*ft_ftoa(double n)
// {
// 	int nb;
// 	double nb_t;
// 	char *tmp1;
// 	char *tmp;
// 	char *ret;
// 	int count;

// 	nb = n / 1;
// 	count = 0;
// 	tmp = ft_itoa(nb);
// 	tmp1 = ft_strjoin(tmp, ".");
// 	free(tmp);
// 	nb_t = n - nb;
// 	while (nb_t != 0)
// 	{
// 		nb_t -= nb;
// 		count++;
// 		nb_t *= 10;
// 		nb = nb_t / 1;
// 	}
// 	nb_t = n - nb;

// 	if (!(tmp = (char *)malloc(sizeof(char) * count + 1)))
// 		ft_error(MALLOC, "(=> ft_ftoa)-(ft_time.c)");
// 	count = 0;
// 	while (nb_t < 1)
// 	{
// 		nb = nb_t / 1;
// 		nb_t -= nb;
// 		tmp[count] = '0' + nb;
// 		count++;
// 		nb_t *= 10;
// 	}
// 	tmp[count] = '\0';
// 	ret = ft_strjoin(tmp1, tmp);
// 	free(tmp1);
// 	free(tmp);
// 	return (ret);
// }

static void	print_t(t_timex *t, int i)
{
	char		*tab[3];
	long int	tabval[3];
	char 		*time;
	// double		tmp;

	tab[0] = "temps du parseur :\t\t\t";
	tab[1] = "temps du lancer de rayon :\t\t";
	tab[2] = "temps total d'execution :\t\t";
	tabval[0] = t->pars;
	tabval[1] = t->ray;
	tabval[2] = t->total;
	write(1, tab[i], ft_strlen(tab[i]));
	// tmp = (tabval[i]) / 1000000;
	time = ft_itoa(tabval[i]);
	ft_putstr(time);
	ft_putstr("usec\n");
	free(time);
}

static void	print_time(t_timex *t)
{
	if (t->pars_f)
		print_t(t, 0);
	if (t->ray_f)
		print_t(t, 1);
	if (t->total_f)
		print_t(t, 2);
}

void	time_mode(char *str, t_env *e)
{
	struct timeval	before;
	struct timeval	after;

	if (e->chrono->ray_f || e->chrono->pars_f || e->chrono->total_f)
	{
		gettimeofday(&(before), NULL);
		ft_parse(str, e);
		gettimeofday(&(after), NULL);
		e->chrono->pars = ((after.tv_sec - before.tv_sec) * 1000000 + after.tv_usec) - before.tv_usec;
		init_mlx(e);
		gettimeofday(&(before), NULL);
		pthread_ray(e);
		gettimeofday(&(after), NULL);
		e->chrono->ray = ((after.tv_sec - before.tv_sec) * 1000000 + after.tv_usec) - before.tv_usec;
		e->chrono->total = e->chrono->ray + e->chrono->pars;
		print_time(e->chrono);
	}
	else
		ft_error(NUMBER_ARG, "rtv1 [Path of file] [-rpt]");
}