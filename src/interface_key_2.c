/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_key_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 12:37:13 by shamdani          #+#    #+#             */
/*   Updated: 2017/07/13 15:09:23 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

char		*ft_print_key_4_2(int key, t_envg *e)
{
	if (key == 5)
		return ((e->shift == 1) ? "g" : "G");
	else if (key == 4)
		return ((e->shift == 1) ? "h" : "H");
	else if (key == 38)
		return ((e->shift == 1) ? "j" : "J");
	else if (key == 40)
		return ((e->shift == 1) ? "k" : "K");
	else
		return ((e->shift == 1) ? "l" : "L");
}

char		*ft_print_key_5_2(int key, t_envg *e)
{
	if (key == 9)
		return ((e->shift == 1) ? "v" : "V");
	else if (key == 11)
		return ((e->shift == 1) ? "b" : "B");
	else if (key == 45)
		return ((e->shift == 1) ? "n" : "N");
	else
		return ((e->shift == 1) ? "m" : "M");
}

static char	*ft_print_key_8(int key, t_envg *e)
{
	if (key == 82)
		return ("0");
	if (key == 65)
		return (".");
	if (key == 76)
		return ("enter");
	if (key == 123)
		return ("left");
	if (key == 124)
		return ("right");
	if (key == 125)
		return ("down");
	if (key == 126)
		return ("up");
	(void)e;
	return ("\0");
}

static char	*ft_print_key_7(int key, t_envg *e)
{
	if (key == 67)
		return ("* (pad)");
	if (key == 89)
		return ("7");
	if (key == 91)
		return ("8");
	if (key == 92)
		return ("9");
	if (key == 78)
		return ("-");
	if (key == 86)
		return ("4");
	if (key == 87)
		return ("5");
	if (key == 88)
		return ("6");
	if (key == 69)
		return ("+ (pad)");
	if (key == 83)
		return ("1");
	if (key == 84)
		return ("2");
	if (key == 85)
		return ("3");
	return (ft_print_key_8(key, e));
}

char		*ft_print_key_6(int key, t_envg *e)
{
	if (key == 260)
		return ("right command");
	if (key == 262)
		return ("right option");
	if (key == 269)
		return ("right control");
	if (key == 279)
		return ("fn");
	if (key == 115)
		return ("home");
	if (key == 116)
		return ("page up");
	if (key == 117)
		return ("right delete");
	if (key == 119)
		return ("end");
	if (key == 121)
		return ("page down");
	if (key == 71)
		return ("clear (pad)");
	if (key == 81)
		return ("= (pad)");
	if (key == 75)
		return ("/ (pad)");
	return (ft_print_key_7(key, e));
}
