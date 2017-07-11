/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_save_img.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 12:21:21 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/30 16:41:10 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../includes/interface_rt.h"


void    init_header(t_bmp *bmp, int w, int h)
{
    bmp->f_header[0] = 'B';
    bmp->f_header[1] = 'M';
    bmp->f_header[10] = 54;
    bmp->i_header[0] = 40;
    bmp->i_header[12] = 1;
    bmp->i_header[14] = 24;
    bmp->f_header[2] = (unsigned char)(bmp->f_size);
    bmp->f_header[3] = (unsigned char)(bmp->f_size>> 8);
    bmp->f_header[4] = (unsigned char)(bmp->f_size>>16);
    bmp->f_header[5] = (unsigned char)(bmp->f_size>>24);
    bmp->i_header[4] = (unsigned char)w;
    bmp->i_header[5] = (unsigned char)(w>> 8);
    bmp->i_header[6] = (unsigned char)(w>>16);
    bmp->i_header[7] = (unsigned char)(w>>24);
    bmp->i_header[8] = (unsigned char)h;
    bmp->i_header[9] = (unsigned char)(h>>8);
    bmp->i_header[10] = (unsigned char)(h>>16);
    bmp->i_header[11] = (unsigned char)(h>>24);
    bmp->pad[0]=0;
    bmp->pad[1]=0;
    bmp->pad[2]=0;
}

int     bmp_save_img (t_envg *e)
{
    static unsigned int s_i = 0;    
    char *pos;
    int i;
    int j;
    char *id;
    unsigned char img[54 + 3 * e->e->mlx->h * e->e->mlx->w / e->e->anti_a / e->e->anti_a];

    e->bmp.img = img;
    e->bmp.f_size = 54 + 3 * e->e->mlx->h * e->e->mlx->w / e->e->anti_a / e->e->anti_a;
    i = 0;
    while (i < (int)e->bmp.f_size - 54)
        e->bmp.img[i++] = 0;
    i = 0;
    while (i < e->e->mlx->w / e->e->anti_a)
    {
        j = 0;
        while (j < e->e->mlx->h / e->e->anti_a)
        {
            pos = e->e->mlx->data + j * e->e->mlx->sizeline + e->e->mlx->bpp / 8 * i;
            e->bmp.img[(i + j * e->e->mlx->w / e->e->anti_a) * 3 + 2] = (unsigned char)*(pos + 2);
            e->bmp.img[(i + j * e->e->mlx->w / e->e->anti_a) * 3 + 1] = (unsigned char)*(pos + 1);
            e->bmp.img[(i + j * e->e->mlx->w / e->e->anti_a) * 3] = (unsigned char)*(pos);
            j++;
        }
        i++;
    }
    i = 0;
    while (i < 14)
        e->bmp.f_header[i++] = 0;
    i = 0;
    while (i < 40)
        e->bmp.i_header[i++] = 0;
    init_header(&e->bmp, e->e->mlx->w / e->e->anti_a, e->e->mlx->h / e->e->anti_a);
    id = ft_itoa(s_i);
    ft_strcat(e->bmp.name, "image_file/image_");
    ft_strcat(e->bmp.name, id);
    ft_strcat(e->bmp.name, ".bmp");
    e->bmp.f = fopen(e->bmp.name,"wb");
    fwrite(e->bmp.f_header, 1, 14, e->bmp.f);
    fwrite(e->bmp.i_header, 1, 40, e->bmp.f);
    i = 0;
    while (i < e->e->mlx->h / e->e->anti_a)
    {
        fwrite(e->bmp.img + (e->e->mlx->w / e->e->anti_a * (e->e->mlx->h / e->e->anti_a - i - 1) * 3), 3, e->e->mlx->w / e->e->anti_a, e->bmp.f);
        fwrite(e->bmp.pad, 1, (4 - (e->e->mlx->w / e->e->anti_a * 3) % 4) % 4, e->bmp.f);
        i++;
    }
    fclose(e->bmp.f);
    i = ft_strlen(e->bmp.name);
    while (i >= 0)
    	e->bmp.name[i--] = '\0';
    s_i++;
    free(id);
    return (1);
}