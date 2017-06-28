/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_modify_delete3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-maul <pde-maul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 15:31:19 by pde-maul          #+#    #+#             */
/*   Updated: 2017/06/28 15:31:37 by pde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/interface_rt.h"
#include "../includes/norme.h"

void			del_elem(t_envg *e, int i)
{
	if (e->light >= 0)
		del_light(e, i);
	else
		del_obj(e, i);
}

void			del_light2(t_parse_light *b, t_parse_light *f_l)
{
	while (b->next)
	{
		if (b->next == f_l)
		{
			f_l = b->next;
			b->next = f_l->next;
			free(f_l->light.name);
			free(f_l);
			f_l = NULL;
			break ;
		}
		b = b->next;
	}
}
