/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_obj_json.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 13:32:28 by phmoulin          #+#    #+#             */
/*   Updated: 2017/06/29 16:22:20 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void     copy_square(t_parse_obj *obj, int fd, t_env *e)
{
    ft_putstr_fd(fd, "\t\"square\" :\n\t{\n\t\t\"name\": ", obj->obj.name, ",",
     NULL);

    ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_ftoa(obj->obj.radius), ",\n", NULL);
    ///debut pos
    ft_putstr_fd(fd, "\t\t\"pos\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.pos.x),
     NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"y\" : ", ft_ftoa(obj->obj.pos.y), ",\n\t\t\t\"z\" : ",
     NULL);
    ft_putstr_fd(fd, ft_ftoa(obj->obj.pos.z), "\n\t\t},\n", NULL);
    ///Fin pos
    ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_itoa(obj->obj.ind_refrac), ",\n",
     NULL);
    ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_itoa(obj->obj.ind_reflec), ",\n",
     NULL);
    ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_itoa(obj->obj.ind_transp), ",\n",
     NULL);
    // ft_putstr_fd(fd, "\t\t\"negatif\" : ", ft_)
    ft_putstr_fd(fd, "\t\t\"color\" :\n\t\t{\n\t\t\t\"r\" : ", ft_itoa((int)obj->obj.color.r),
         NULL);
//      printf("CUBE %c \n", obj->obj.color.g);
    ft_putstr_fd(fd, ",\n\t\t\t\"g\" : ",  ft_itoa((int)obj->obj.color.g), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)obj->obj.color.b), "\n\t\t},", NULL);
    ft_putstr_fd(fd, "\n\t\t\"angle\" : ", ft_itoa(obj->obj.angle), ",\n\t\t", NULL);
    ft_putstr_fd(fd, "\"dir\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.dir.x),
     ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_ftoa(obj->obj.dir.y), ",\n\t\t\t", NULL);
    ft_putstr_fd(fd, "\"z\" : ", ft_ftoa(obj->obj.dir.z), "\n\t\t},\n", NULL);
    if (obj->obj.id_texture > 0)
        ft_putstr_fd(fd, "\t\t\"texture\" : \"", e->path_tex[(int)obj->obj.id_texture - 1], "\"", NULL);
    ft_putstr_fd(fd, "\n\t},\n", NULL);
         obj = obj->next;
}

static void     copy_cube(t_parse_obj *obj, int fd, t_env *e)
{
    ft_putstr_fd(fd, "\t\"cube\" :\n\t{\n\t\t\"name\": \"", obj->obj.name, "\",",
     NULL);
    ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_ftoa(obj->obj.radius), ",\n", NULL);
    ///debut pos
    ft_putstr_fd(fd, "\t\t\"pos\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.pos.x),
     NULL);
    ft_putstr_fd(fd, "\n\t\t\t\"y\" : ", ft_ftoa(obj->obj.pos.y), ",\n\t\t\t\"z\" : ", NULL);
    ft_putstr_fd(fd, ft_ftoa(obj->obj.pos.z), "\n\t\t},\n", NULL);
    ///Fin pos
    ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_itoa(obj->obj.ind_refrac), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_itoa(obj->obj.ind_reflec), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_itoa(obj->obj.ind_transp), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"color\" :\n\t\t{\n\t\t\t\"r\" : ", ft_itoa((int)obj->obj.color.r), NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"g\" : ",  ft_itoa((int)obj->obj.color.g), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)obj->obj.color.b), "\n\t\t},", NULL);
    ft_putstr_fd(fd, "\t\t\"angle\" : ", ft_itoa(obj->obj.angle), ",\n\t\t", NULL);
    ft_putstr_fd(fd, "\"dir\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.dir.x),
     ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_ftoa(obj->obj.dir.y), ",\n\t\t\t", NULL);
    ft_putstr_fd(fd, "\"z\" : ", ft_ftoa(obj->obj.dir.z), "\n\t\t},\n", NULL);
    if (obj->obj.id_texture > 0)
        ft_putstr_fd(fd, "\t\t\"texture\" : \"", e->path_tex[(int)obj->obj.id_texture - 1], "\"", NULL);
    ft_putstr_fd(fd, "\n\t},\n", NULL);
    obj = obj->next;
}

static void     copy_sphere(t_parse_obj *obj, int fd, t_env *e)
{
    ft_putstr_fd(fd, "\t\"sphere\" :\n\t{\n\t\t\"name\": \"", obj->obj.name, "\",",
    NULL);
    ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_ftoa(obj->obj.radius), ",\n", NULL);
    ///debut pos
    ft_putstr_fd(fd, "\t\t\"pos\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.pos.x), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_ftoa(obj->obj.pos.y), ",\n\t\t\t\"z\" : ",
     NULL);
    ft_putstr_fd(fd, ft_ftoa(obj->obj.pos.z), "\n\t\t},\n", NULL);
    ///Fin pos
    ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_itoa(obj->obj.ind_refrac), ",\n",
     NULL);
    ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_itoa(obj->obj.ind_reflec), ",\n",
     NULL);
    ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_itoa(obj->obj.ind_transp), ",\n",
     NULL);
    ft_putstr_fd(fd, "\t\t\"color\" :\n\t\t{\n\t\t\t\"r\" : ", ft_itoa((int)obj->obj.color.r),
         NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"g\" : ", ft_itoa((int)obj->obj.color.g), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)obj->obj.color.b), "\n\t\t},\n", NULL);
    if (obj->obj.id_texture > 0)
        ft_putstr_fd(fd, "\t\t\"texture\" : \"", e->path_tex[(int)obj->obj.id_texture - 1], "\"", NULL);
    ft_putstr_fd(fd, "\n\t},\n", NULL);
    obj = obj->next;

}

static void     copy_plan(t_parse_obj *obj, int fd, t_env *e)
{
    ft_putstr_fd(fd, "\t\"plane\" :\n\t{\n\t\t\"name\": \"", obj->obj.name, "\",",
     NULL);
    //ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_ftoa(obj->obj.radius), ",\n", NULL);
    ///debut pos
    ft_putstr_fd(fd, "\n\t\t\"pos\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.pos.x),
     NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"y\" : ", ft_ftoa(obj->obj.pos.y), ",\n\t\t\t\"z\" : ", NULL);
    ft_putstr_fd(fd, ft_ftoa(obj->obj.pos.z), "\n\t\t},\n", NULL);
    ///Fin pos
    ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_itoa(obj->obj.ind_refrac), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_itoa(obj->obj.ind_reflec), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_itoa(obj->obj.ind_transp), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"color\" :\n\t\t{\n\t\t\t\"r\" : ", ft_itoa((int)obj->obj.color.r), NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"g\" : ",  ft_itoa((int)obj->obj.color.g), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)obj->obj.color.b), "\n\t\t},", NULL);
    //ft_putstr_fd(fd, "\n\t\t\"angle\" : ", ft_itoa(obj->obj.angle), ",\n\t\t", NULL);
    ft_putstr_fd(fd, "\n\t\t\"dir\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.dir.x),
     ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_ftoa(obj->obj.dir.y), ",\n\t\t\t", NULL);
    ft_putstr_fd(fd, "\"z\" : ", ft_ftoa(obj->obj.dir.z), "\n\t\t},\n", NULL);
    if (obj->obj.id_texture > 0)
        ft_putstr_fd(fd, "\t\t\"texture\" : \"", e->path_tex[(int)obj->obj.id_texture - 1], "\"", NULL);
    ft_putstr_fd(fd, "\n\t},\n", NULL);
    obj = obj->next;
}

static void     copy_cylindre(t_parse_obj *obj, int fd, t_env *e)
{
    ft_putstr_fd(fd, "\t\"cylinder\" :\n\t{\n\t\t\"name\": \"", obj->obj.name, "\",",
     NULL);
    ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_ftoa(obj->obj.radius), ",\n", NULL);
    ///debut pos
    ft_putstr_fd(fd, "\t\t\"pos\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.pos.x),
     NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"y\" : ", ft_ftoa(obj->obj.pos.y), ",\n\t\t\t\"z\" : ", NULL);
    ft_putstr_fd(fd, ft_ftoa(obj->obj.pos.z), "\n\t\t},\n", NULL);
    ///Fin pos
    ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_itoa(obj->obj.ind_refrac), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_itoa(obj->obj.ind_reflec), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_itoa(obj->obj.ind_transp), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"color\" :\n\t\t{\n\t\t\t\"r\" : ", ft_itoa((int)obj->obj.color.r), NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"g\" : ",  ft_itoa((int)obj->obj.color.g), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)obj->obj.color.b), "\n\t\t},", NULL);
    ft_putstr_fd(fd, "\n\t\t\"dir\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.dir.x),
     ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_ftoa(obj->obj.dir.y), ",\n\t\t\t", NULL);
    ft_putstr_fd(fd, "\"z\" : ", ft_ftoa(obj->obj.dir.z), "\n\t\t},\n", NULL);
    if (obj->obj.id_texture > 0)
        ft_putstr_fd(fd, "\t\t\"texture\" : \"", e->path_tex[(int)obj->obj.id_texture - 1], "\"", NULL);
    ft_putstr_fd(fd, "\n\t},\n", NULL);
    obj = obj->next;
}
static void     copy_cone(t_parse_obj *obj, int fd, t_env *e)
{
    ft_putstr_fd(fd, "\t\"cone\" :\n\t{\n\t\t\"name\": \"", obj->obj.name, "\",",
     NULL);
    ft_putstr_fd(fd, "\n\t\t\"angle\" : ", ft_ftoa(obj->obj.angle), ",\n", NULL);
    ///debut pos
    ft_putstr_fd(fd, "\t\t\"pos\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.pos.x), NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"y\" : ", ft_ftoa(obj->obj.pos.y), ",\n\t\t\t\"z\" : ", NULL);
    ft_putstr_fd(fd, ft_ftoa(obj->obj.pos.z), "\n\t\t},\n", NULL);
    ///Fin pos
    ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_itoa(obj->obj.ind_refrac), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_itoa(obj->obj.ind_reflec), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_itoa(obj->obj.ind_transp), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"color\" :\n\t\t{\n\t\t\t\"r\" : ", ft_itoa((int)obj->obj.color.r), NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"g\" : ",  ft_itoa((int)obj->obj.color.g), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)obj->obj.color.b), "\n\t\t},", NULL);
    ft_putstr_fd(fd, "\t\t\"angle\" : ", ft_itoa(obj->obj.angle), ",\n\t\t", NULL);
    ft_putstr_fd(fd, "\"dir\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.dir.x),
     ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_ftoa(obj->obj.dir.y), ",\n\t\t\t", NULL);
    ft_putstr_fd(fd, "\"z\" : ", ft_ftoa(obj->obj.dir.z), "\n\t\t},\n", NULL);
    if (obj->obj.id_texture > 0)
        ft_putstr_fd(fd, "\t\t\"texture\" : \"", e->path_tex[(int)obj->obj.id_texture - 1], "\"", NULL);
    ft_putstr_fd(fd, "\n\t},\n", NULL);
    obj = obj->next;
}

static void     copy_circle(t_parse_obj *obj, int fd, t_env *e)
{
    ft_putstr_fd(fd, "\t\"circle\" :\n\t{\n\t\t\"name\": \"", obj->obj.name, "\",",
     NULL);
    ft_putstr_fd(fd, "\n\t\t\"radius\" : ", ft_ftoa(obj->obj.radius), ",\n", NULL);
    ///debut pos
    ft_putstr_fd(fd, "\t\t\"pos\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.pos.x),
     NULL);
    ft_putstr_fd(fd, "\n\t\t\t\"y\" : ", ft_ftoa(obj->obj.pos.y), ",\n\t\t\t\"z\" : ", NULL);
    ft_putstr_fd(fd, ft_ftoa(obj->obj.pos.z), "\n\t\t},\n", NULL);
    ///Fin pos
    ft_putstr_fd(fd, "\t\t\"ind_refrac\" : ", ft_itoa(obj->obj.ind_refrac), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_reflec\" : ", ft_itoa(obj->obj.ind_reflec), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"ind_transp\" : ", ft_itoa(obj->obj.ind_transp), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\"color\" :\n\t\t{\n\t\t\t\"r\" : ", ft_itoa((int)obj->obj.color.r), NULL);
    ft_putstr_fd(fd, ",\n\t\t\t\"g\" : ",  ft_itoa((int)obj->obj.color.g), ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"b\" : ", ft_itoa((int)obj->obj.color.b), "\n\t\t},", NULL);
    ft_putstr_fd(fd, "\t\t\"angle\" : ", ft_itoa(obj->obj.angle), ",\n\t\t", NULL);
    ft_putstr_fd(fd, "\"dir\" :\n\t\t{\n\t\t\t\"x\" : ", ft_ftoa(obj->obj.dir.x),
     ",\n", NULL);
    ft_putstr_fd(fd, "\t\t\t\"y\" : ", ft_ftoa(obj->obj.dir.y), ",\n\t\t\t", NULL);
    ft_putstr_fd(fd, "\"z\" : ", ft_ftoa(obj->obj.dir.z), "\n\t\t},\n", NULL);
    if (obj->obj.id_texture > 0)
        ft_putstr_fd(fd, "\t\t\"texture\" : \"", e->path_tex[(int)obj->obj.id_texture - 1], "\"", NULL);
    ft_putstr_fd(fd, "\n\t},\n", NULL);
    obj = obj->next;
}

static int           save_obj(t_env *e, t_parse_obj *obj, int fd)
{
    if (obj != NULL)
    {
        while (obj)
        {
            if (obj->obj.type == 6)
                copy_square(obj, fd, e);
            else if (obj->obj.type == 7)
                copy_cube(obj, fd, e);
            else if (obj->obj.type == 1)
                copy_sphere(obj, fd, e);
            else if (obj->obj.type == 2)
                copy_plan(obj, fd, e);
            else if (obj->obj.type == 3)
                copy_cylindre(obj, fd, e);
            else if (obj->obj.type == 4)
                copy_cone(obj, fd, e);
            else if (obj->obj.type == 5)
                copy_circle(obj, fd, e);
            obj = obj->next;
        }
        return (1);
    }
    return (-1);
}

void            save_scene(t_env *e)
{
    static int  i = 0;
    int         fd;
    char        *id;
    char        name[256];
    t_parse_obj     *obj;
    t_parse_light   *light;

    light = e->parse_light;
    fd = -1;
    obj = NULL;
    obj = e->parse_obj;
    id = ft_itoa(i);
    ft_strcpy(name, "./scenes_file/scene_file_");
    ft_strcat(name, id);
    ft_strcat(name, ".json");
    printf("%s\n", name);
    if ((fd = open(name, O_CREAT | O_WRONLY , 0644)) <= 0)
        ft_error("fichier deja existant", " save_scene");
    ft_putstr_fd(fd, "{\n\t\"anti-aliasing\" : ", ft_itoa(e->anti_a), NULL);
    ft_putstr_fd(fd, ",\n\t\"ambient\" : ", ft_ftoa(e->amb), ",\n", NULL);
    save_obj(e, obj, fd);
    save_light_and_cam(e, fd, light);
    ft_putstr_fd(fd, "}", NULL);
    free(id);
    i++;
}
