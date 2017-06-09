/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_and_apply_filtre.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:25:53 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/09 11:30:14 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int  *lecture_img_for_blur(t_env *e, int x, int y, int i)
{
  int     *tab = NULL;
  int     compt;
  int     s;

  s = x;
  compt = 0;
    if (!(tab = (int *)malloc(sizeof(int) * 100)))
      ft_error(MALLOC, "lecture_img_to_blur");
  while (i < 100 && y < e->mlx->h)
  {
      tab[i++] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
        ((e->mlx->bpp / 8) * x) + 2];
      tab[i++] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
        ((e->mlx->bpp / 8) * x) + 1];
      tab[i++] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
        ((e->mlx->bpp / 8) * x)];
      tab[i++] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
        ((e->mlx->bpp / 8) * x++) + 3];
      if (x > e->mlx->w || compt++ == 5)
      {
        y++;
        x = s;
        compt = 0;
      }
    }
    return (tab);
}

int  apply_color_pix_for_blur(t_env *e, int *rgb, int x, int y)
{
  if (y >= e->mlx->h || x >= e->mlx->w)
    return (0);
    rgb[0] = rgb[0] / 256;
    rgb[1] = rgb[1] / 256;
    rgb[2] = rgb[2] / 256;
    rgb[3] = rgb[3] / 256;
    if (rgb[0] > 255)
      rgb[0] = 255;
    if (rgb[1] > 255)
      rgb[1] = 255;
    if (rgb[2] > 255)
      rgb[2] = 255;
    if (rgb[3] > 255)
      rgb[3] = 255;
    e->mlx->data[(y * e->mlx->sizeline) + \
        ((e->mlx->bpp / 8) * x) + 2] = (unsigned char)rgb[0];
    e->mlx->data[(y * e->mlx->sizeline) + \
        ((e->mlx->bpp / 8) * x) + 1] = (unsigned char)rgb[1];
    e->mlx->data[(y * e->mlx->sizeline) + \
        ((e->mlx->bpp / 8) * x)] = (unsigned char)rgb[2];
    e->mlx->data[(y * e->mlx->sizeline) + \
        ((e->mlx->bpp / 8) * x) + 3] = (unsigned char)rgb[3];
    return (0);
}

void  lecture_img(t_env *e, int **rgb, int x, int y)
{
      rgb[0][0] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
      ((e->mlx->bpp / 8) * x) + 2];
      rgb[0][1] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
      ((e->mlx->bpp / 8) * x) + 1];
      rgb[0][2] = (unsigned char)e->mlx->data[(y * e->mlx->sizeline) + \
      ((e->mlx->bpp / 8) * x)];
}

void apply_color_pix(t_env *e, int *rgb, int x, int y)
{
  e->mlx->data[(y * e->mlx->sizeline) + \
      ((e->mlx->bpp / 8) * x) + 2] = (unsigned char)rgb[0];
  e->mlx->data[(y * e->mlx->sizeline) + \
      ((e->mlx->bpp / 8) * x) + 1] = (unsigned char)rgb[1];
  e->mlx->data[(y * e->mlx->sizeline) + \
      ((e->mlx->bpp / 8) * x)] = (unsigned char)rgb[2];
}

void      choice_filter(t_env *e)
{
  int    *rgb;

  if ((rgb = (int *)malloc(sizeof(int) * 5)) == NULL)// a secur;
      ft_error(MALLOC, "choice_filter");
  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;
  rgb[3] = 0;

  if (e->flag == 1)
    filter_blue(e, rgb, 0, 0);
  else if (e->flag == 2)
    filter_green(e, rgb, 0, 0);
  else if (e->flag == 3)
    filter_red(e, rgb, 0, 0);
  else if (e->flag == 4)
    filter_sepia(e, rgb, 0, 0);
  else if (e->flag == 5)
    filter_blur(e, rgb, 0, 0);
  else if (e->flag == 6)
    filter_blur(e, rgb, 0, 0); // verifier les derniere ligne de pixel et leurs couleur !
  //filter_cartoon(e, rgb, 0, 0);
  free(rgb);
  printf("filter finish\n");
}
