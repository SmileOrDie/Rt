/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phmoulin <phmoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:25:48 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/09 11:27:37 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void     filter_sepia(t_env *e, int *rgb, int x, int y)
{
  int r2;
  int g2;
  int b2;
  double    sepia = 1; // a remplacer par la struct pour opaciter
  //
  r2 = 0;
  b2 = 0;
  g2 = 0;
  while (y <= e->mlx->h)
  {
      lecture_img(e, &rgb, x, y);// recuprer les couleur de img
      r2 = (0.393 * rgb[0] + 0.769 * rgb[1] + 0.189 * rgb[2]) * sepia + (1 - sepia) * rgb[0];
      g2 = (0.349 * rgb[0] + 0.686 * rgb[1] + 0.168 * rgb[2]) * sepia + (1 - sepia) * rgb[1];
      b2 = (0.272 * rgb[0] + 0.534 * rgb[1] + 0.131 * rgb[2]) * sepia + (1 - sepia) * rgb[2];
      rgb[0] = r2;
      rgb[1] = g2;
      rgb[2] = b2;
      if (rgb[0] > 255)
        rgb[0] = 255;
      if (rgb[1] > 255)
        rgb[1] = 255;
        if (rgb[2] > 255)
        rgb[2] = 255;
       apply_color_pix(e, rgb, x, y); // print les nouvelle couleur
        x++;

      if (x >= e->mlx->w)
      {
        y++;
        x = 0;
      }
    }
}

void     filter_red(t_env *e, int *rgb, int x, int y)
{
  int r2;
  int g2;
  int b2;
  double    red = 0.5; // a remplacer par la struct pour opaciter
  //
  r2 = 0;
  b2 = 0;
  g2 = 0;
  while (y <= e->mlx->h)
  {
    lecture_img(e, &rgb, x, y);// recuprer les couleur de img
    r2 = (rgb[0] * 0.4 + 255 * 0.6) * red + (1 - red) * rgb[0];
    g2 = (rgb[1] * 0.4 + 0 * 0.6) * red + (1 - red) * rgb[1];
    b2 = (rgb[2] * 0.4 + 0 * 0.6) * red + (1 - red) * rgb[2];
    rgb[0] = r2;
    rgb[1] = g2;
    rgb[2] = b2;
    if (rgb[0] > 255)
      rgb[0] = 255;
    if (rgb[1] > 255)
      rgb[1] = 255;
    if (rgb[2] > 255)
      rgb[2] = 255;
     apply_color_pix(e, rgb, x, y); // print les nouvelle couleur
    x++;
    if (x >= e->mlx->w)
    {
      y++;
      x = 0;
    }
  }
}

void     filter_blue(t_env *e, int *rgb, int x, int y)
{
  int r2;
  int g2;
  int b2;
  double    blue = 1; // a remplacer par la struct pour opaciter
  //
  r2 = 0;
  b2 = 0;
  g2 = 0;
  while (y <= e->mlx->h)
  {
    lecture_img(e, &rgb, x, y);// recuprer les couleur de img
    r2 = (rgb[0] * 0.4 + 0 * 0.6) * blue + (1 - blue) * rgb[0];
    g2 = (rgb[1] * 0.4 + 0 * 0.6) * blue + (1 - blue) * rgb[1];
    b2 = (rgb[2] * 0.4 + 255 * 0.6) * blue + (1 - blue) * rgb[2];
    rgb[0] = r2;
    rgb[1] = g2;
    rgb[2] = b2;
    if (rgb[0] > 255)
      rgb[0] = 255;
    if (rgb[1] > 255)
      rgb[1] = 255;
    if (rgb[2] > 255)
      rgb[2] = 255;
     apply_color_pix(e, rgb, x, y); // print les nouvelle couleur
    x++;
    if (x >= e->mlx->w)
    {
      y++;
      x = 0;
    }
  }
}

void     filter_green(t_env *e, int *rgb, int x, int y)
{
  int r2;
  int g2;
  int b2;
  double    green = 0.5; // a remplacer par la struct pour opaciter
  //
  r2 = 0;
  b2 = 0;
  g2 = 0;
  while (y <= e->mlx->h)
  {
    lecture_img(e, &rgb, x, y);// recuprer les couleur de img
    r2 = (rgb[0] * 0.4 + 0 * 0.6) * green + (1 - green) * rgb[0];
    g2 = (rgb[1] * 0.4 + 0 * 0.6) * green + (1 - green) * rgb[1];
    b2 = (rgb[2] * 0.4 + 255 * 0.6) * green + (1 - green) * rgb[2];
    rgb[0] = r2;
    rgb[1] = g2;
    rgb[2] = b2;
    if (rgb[0] > 255)
      rgb[0] = 255;
    if (rgb[1] > 255)
      rgb[1] = 255;
    if (rgb[2] > 255)
      rgb[2] = 255;
     apply_color_pix(e, rgb, x, y); // print les nouvelle couleur
    x++;
    if (x >= e->mlx->w)
    {
      y++;
      x = 0;
    }
  }
}
