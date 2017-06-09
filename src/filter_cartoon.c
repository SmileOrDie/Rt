/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cartoon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:48:33 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/09 10:13:35 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
void    static apply_cart_to_r(int *rgb, int i, int *tab)
{
  rgb[0] = tab[i - 50] * 1 + tab[i - 46] * 1 + tab[i - 42] * 1
          + tab[i - 38] * 1 + tab[i - 34] * 1
          + tab[i - 30] * 1 + tab[i - 26] * 4 + tab[i - 22] * 4
          + tab[i - 18] * 4 + tab[i - 14] * 1
          + tab[i - 10] * 1 + tab[i - 6] * 4 + tab[i - 2] * 12
          + tab[i + 2] * 4 + tab[i + 6] * 1
          + tab[i + 10] * 1 + tab[i + 14] * 4 + tab[i + 18] * 4
          + tab[i + 22] * 4 + tab[i + 26] * 1
          + tab[i + 30] * 1 + tab[i + 34] * 1 + tab[i + 38] * 1
          + tab[i + 42] * 1 + tab[i + 46] * 1;
}

void    static apply_cart_to_g(int *rgb, int i, int *tab)
{
  rgb[1] = tab[i - 50] * 1 + tab[i - 46] * 1 + tab[i - 42] * 1
          + tab[i - 38] * 1 + tab[i - 34] * 1
          + tab[i - 30] * 1 + tab[i - 26] * 4 + tab[i - 22] * 4
          + tab[i - 18] * 4 + tab[i - 14] * 1
          + tab[i - 10] * 1 + tab[i - 6] * 4 + tab[i - 2] * 12
          + tab[i + 2] * 4 + tab[i + 6] * 1
          + tab[i + 10] * 1 + tab[i + 14] * 4 + tab[i + 18] * 4
          + tab[i + 22] * 4 + tab[i + 26] * 1
          + tab[i + 30] * 1 + tab[i + 34] * 1 + tab[i + 38] * 1
          + tab[i + 42] * 1 + tab[i + 46] * 1;
}

void    static apply_cart_to_b(int *rgb, int i, int *tab)
{
  rgb[2] = tab[i - 50] * 1 + tab[i - 46] * 1 + tab[i - 42] * 1
          + tab[i - 38] * 1 + tab[i - 34] * 1
          + tab[i - 30] * 1 + tab[i - 26] * 4 + tab[i - 22] * 4
          + tab[i - 18] * 4 + tab[i - 14] * 1
          + tab[i - 10] * 1 + tab[i - 6] * 4 + tab[i - 2] * 12
          + tab[i + 2] * 4 + tab[i + 6] * 1
          + tab[i + 10] * 1 + tab[i + 14] * 4 + tab[i + 18] * 4
          + tab[i + 22] * 4 + tab[i + 26] * 1
          + tab[i + 30] * 1 + tab[i + 34] * 1 + tab[i + 38] * 1
          + tab[i + 42] * 1 + tab[i + 46] * 1;
}

void    static apply_cart_to_t(int *rgb, int i, int *tab)
{
  rgb[3] = tab[i - 50] * 1 + tab[i - 46] * 1 + tab[i - 42] * 1
          + tab[i - 38] * 1 + tab[i - 34] * 1
          + tab[i - 30] * 1 + tab[i - 26] * 4 + tab[i - 22] * 4
          + tab[i - 18] * 4 + tab[i - 14] * 1
          + tab[i - 10] * 1 + tab[i - 6] * 4 + tab[i - 2] * 12
          + tab[i + 2] * 4 + tab[i + 6] * 1
          + tab[i + 10] * 1 + tab[i + 14] * 4 + tab[i + 18] * 4
          + tab[i + 22] * 4 + tab[i + 26] * 1
          + tab[i + 30] * 1 + tab[i + 34] * 1 + tab[i + 38] * 1
          + tab[i + 42] * 1 + tab[i + 46] * 1;
}

void    filter_cartoon(t_env *e, int *rgb, int x, int y)
{
     int     *tab = NULL;
     y = 1;
     x = 2;
     while (y <= e->mlx->h - 1)
     {
         tab = lecture_img_for_blur(e, x, y, 0);
         apply_cart_to_r(rgb, 50, tab);
         apply_cart_to_g(rgb, 51, tab);
         apply_cart_to_b(rgb, 52, tab);
         apply_cart_to_t(rgb, 53, tab);
         if (apply_color_pix_for_blur(e, rgb, x, y) == -1)
           break ;
         x++;
        if (x > e->mlx->w)
        {
          y++;
          x = 0;
        }
      }
}
