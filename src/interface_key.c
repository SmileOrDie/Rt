/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:32 by pde-maul          #+#    #+#             */
/*   Updated: 2017/07/13 14:54:05 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"

static char	*ft_print_key_5(int key, t_envg *e)
{
	if (key == 9 || key == 11 || key == 45 || key == 46)
		return (ft_print_key_5_2(key, e));
	if (key == 43)
		return ((e->shift == 1) ? "," : "<");
	if (key == 47)
		return ((e->shift == 1) ? "." : ">");
	if (key == 44)
		return ((e->shift == 1) ? "/" : "?");
	if (key == 258)
	{
		e->shift = (e->shift == 1) ? 0 : 1;
		return ("\0");
	}
	if (key == 256)
		return ("left control");
	if (key == 261)
		return ("left option");
	if (key == 259)
		return ("left command");
	if (key == 49)
		return ("");
	return (ft_print_key_6(key, e));
}

static char	*ft_print_key_4(int key, t_envg *e)
{
	if (key == 5 || key == 4 || key == 38 || key == 40 || key == 37)
		return (ft_print_key_4_2(key, e));
	if (key == 41)
		return ((e->shift == 1) ? ";" : ":");
	if (key == 39)
		return ((e->shift == 1) ? "'" : "\"");
	if (key == 36)
		return ("return");
	if (key == 257)
	{
		e->shift = (e->shift == 1) ? 0 : 1;
		return ("\0");
	}
	if (key == 6)
		return ((e->shift == 1) ? "z" : "Z");
	if (key == 7)
		return ((e->shift == 1) ? "x" : "X");
	if (key == 8)
		return ((e->shift == 1) ? "c" : "C");
	return (ft_print_key_5(key, e));
}

static char	*ft_print_key_3(int key, t_envg *e)
{
	if (key == 16)
		return ((e->shift == 1) ? "y" : "Y");
	if (key == 32)
		return ((e->shift == 1) ? "u" : "U");
	if (key == 34)
		return ((e->shift == 1) ? "i" : "I");
	if (key == 31)
		return ((e->shift == 1) ? "o" : "O");
	if (key == 35)
		return ((e->shift == 1) ? "p" : "P");
	if (key == 33)
		return ((e->shift == 1) ? "[" : "{");
	if (key == 30)
		return ((e->shift == 1) ? "]" : "}");
	if (key == 42)
		return ((e->shift == 1) ? "\\" : "|");
	if (key == 0)
		return ((e->shift == 1) ? "a" : "A");
	if (key == 1)
		return ((e->shift == 1) ? "s" : "S");
	if (key == 2)
		return ((e->shift == 1) ? "d" : "D");
	if (key == 3)
		return ((e->shift == 1) ? "f" : "F");
	return (ft_print_key_4(key, e));
}

static char	*ft_print_key_2(int key, t_envg *e)
{
	if (key == 28)
		return ((e->shift == 1) ? "8" : "*");
	if (key == 25)
		return ((e->shift == 1) ? "9" : "(");
	if (key == 29)
		return ((e->shift == 1) ? "0" : ")");
	if (key == 27)
		return ((e->shift == 1) ? "-" : "_");
	if (key == 24)
		return ((e->shift == 1) ? "=" : "+");
	if (key == 51)
		return ("delete");
	if (key == 48)
		return ("\t");
	if (key == 12)
		return ((e->shift == 1) ? "q" : "Q");
	if (key == 13)
		return ((e->shift == 1) ? "w" : "W");
	if (key == 14)
		return ((e->shift == 1) ? "e" : "E");
	if (key == 15)
		return ((e->shift == 1) ? "r" : "R");
	if (key == 17)
		return ((e->shift == 1) ? "t" : "T");
	return (ft_print_key_3(key, e));
}

char		*ft_print_key(int key, t_envg *e)
{
	if (key == 53)
		return ("echap");
	if (key == 50)
		return ((e->shift == 1) ? "`" : "~");
	if (key == 18)
		return ((e->shift == 1) ? "1" : "!");
	if (key == 19)
		return ((e->shift == 1) ? "2" : "@");
	if (key == 20)
		return ((e->shift == 1) ? "3" : "#");
	if (key == 21)
		return ((e->shift == 1) ? "4" : "$");
	if (key == 23)
		return ((e->shift == 1) ? "5" : "%");
	if (key == 22)
		return ((e->shift == 1) ? "6" : "^");
	if (key == 26)
		return ((e->shift == 1) ? "7" : "&");
	return (ft_print_key_2(key, e));
}
