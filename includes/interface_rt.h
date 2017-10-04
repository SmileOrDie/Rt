/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_rt.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:45:45 by shamdani          #+#    #+#             */
/*   Updated: 2017/08/28 19:04:01 by phmoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_RT_H
# define INTERFACE_RT_H

# include "../libft/includes/libft.h"
# include "rt.h"

# define WI 400
# define HE 950

# define VAL 156000
# define T 2000000

# define ESC 53
# define TILDE 50
# define EXCLAMATION 18
# define ARROBAZE 19
# define ACHTAGE 20
# define DOLLAR 21
# define MODULO 23
# define CIRCOFLEXE 22
# define ET 26
# define ETOILE 28
# define PARENTHESE_O 25
# define PARENTHESE_F 29
# define UNDESCOR 27
# define PLUS 24
# define DELETE_1 51
# define TAB 48
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_T 17
# define KEY_Y 16
# define KEY_U 32
# define KEY_I 34
# define KEY_O 31
# define KEY_P 35
# define CROCHET_O 33
# define CROCHET_F 30
# define ANTISLASH 42

/*
** COMPORTEMENT ETRANGE SUR CAPS
*/

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define POINT_V 41
# define APOSTROPHE 39
# define RETURN 36
# define SHIFT_G 257
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_N 45
# define KEY_M 46
# define VIRGULE 43
# define POINT 47
# define SLACH 44
# define SHIFT_D 258
# define CONTROL_G 256
# define ALT_G 261
# define COMMAND_G 259
# define ESPACE 49
# define COMMAND_D 260
# define ALT_D 262
# define CONTROL_D 269
# define FN 279
# define HOME 115
# define PAGE_UP 116
# define DELETE_2 117
# define END 119
# define PAGE_DOWN 121
# define PAD_CLEAR 71
# define PAD_EGAL 81
# define PAD_SLACH 75
# define PAD_ETOILE 67
# define PAD_7 89
# define PAD_8 91
# define PAD_9 92
# define PAD_TIRET 78
# define PAD_4 86
# define PAD_5 87
# define PAD_6 88
# define PAD_PLUS 69
# define PAD_1 83
# define PAD_2 84
# define PAD_3 85
# define PAD_0 82
# define PAD_POINT 65
# define PAD_ENTER 76
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define LINE_SIZE 128

typedef struct			s_pos_i
{
	int					w;
	int					h;
}						t_pos_i;

typedef struct			s_tab_valid
{
	int					home;
	int					add;
	int					conf;
	int					del;
	int					info;
}						t_tab_valid;

typedef struct			s_filter
{
	int					blue;
	int					green;
	int					red;
	int					sepia;
	int					old;
	int					cartoon;
}						t_filter;

typedef struct			s_tabu
{
	char				*name_path;
	DIR					*dirp;
	int					index;
}						t_tabu;

typedef struct			s_bmp
{
	FILE				*f;
	unsigned char		f_header[14];
	unsigned char		i_header[40];
	unsigned char		pad[3];
	unsigned char		*img;
	unsigned int		f_size;
	char				name[256];
}						t_bmp;

typedef struct			s_envg
{
	t_env				*e;
	t_cam				cam;
	int					group_max;
	char				**path_tex;
	int					nb_tex;
	t_parse_obj			*parse_obj;
	t_parse_light		*parse_light;
	t_mlx				mlx;
	t_mlx				img;
	t_bmp				bmp;
	char				**line;
	int					i_lst;
	int					obj;
	int					light;
	t_pos_i				line_pos[LINE_SIZE];
	t_pos_i				img_pos[LINE_SIZE];
	int					pos;
	int					pos_value[LINE_SIZE];
	int					nb_c;
	int					nb_obj;
	int					font;
	int					f_key;
	t_tab_valid			volet;
	t_filter			filter;
	int					shift;
	int					mod;
	int					page;
	int					run;
	int					error;
	int					id;
	int					anti_a;
	t_pos				win;
	t_tabu				tab_texture;
	t_tabu				tab_scene;
	pthread_t			thread;
	t_env_cl			*cl_e;
	double				amb;
	void				*wait_img[4];
	t_pos				size[4];
}						t_envg;

typedef struct			s_g_pix
{
	char				flag;
	double				coef;
	int					i;
}						t_g_pix;

typedef struct			s_n_g_img
{
	int					tmpx;
	int					tmpy;
	int					tx;
	int					ty;
	int					i;
	int					color[3];
	int					opti[4];
}						t_n_g_img;

void					ft_init_opencl(t_envg *e, t_opencl *cl);
void					init_cl_e(t_env *e, t_env_cl *cl);
void					ft_l_err(int err, int id);
int						keypress(int key, t_envg *e);

/*
** rt_create_env_3.c
*/
void					get_obj_lst(t_envg *e, t_obj obj, int *i);

/*
** rt_create_env_2.c
*/
t_vector				mult_mat(char axe, double theta, t_vector point);

/*
** interface_modify_delete_2.c
*/
void					del_light(t_envg *e, int i);
void					del_obj(t_envg *e, int i);

/*
** interface_modify_delete.c
*/
void					ft_strcpy_nbr(char **dest, double d);
void					modif_light(t_envg *e, int light);
void					modif_list(t_envg *e, int obj);
void					del_elem(t_envg *e, int i);
void					modif_default(t_envg *e);
void					init_id(t_envg *e);

/*
** interface_keypress.c
*/
int						interface_keypress(int key, t_envg *e);
void					free_env_parse(t_envg *e);
void					add_new_texture(t_envg *e);
void					clean_str(char **clean, int f);

/*
** interface_line.c
*/
void					print_line(t_envg *e, int line, int precision);
void					add_line(char *dest, char *src, int f);
void					del_line(t_envg *e);
void					string_put(t_envg *e, int size[2], int color,
	char *str);

/*
** interface_mouse.c
*/
int						interface_mouse_click(int button, int x, int y,
	t_envg *e);
void					ft_exit(t_envg *e);

/*
** interface_key_2.c
*/
char					*ft_print_key_4_2(int key, t_envg *e);
char					*ft_print_key_6(int key, t_envg *e);
char					*ft_print_key_5_2(int key, t_envg *e);

/*
** interface_key.c
*/
char					*ft_print_key(int key, t_envg *e);

/*
** interface_mouse.c
*/
int						mouss_click(int button, int x, int y, t_envg *e);

/*
** interface_mouse_2
*/
int						select_pos(t_envg *e, int x, int y);
void					volet_target(t_envg *e);
void					mousse_click_x(t_envg *e, int x);

/*
** interface_xpm_file.c
*/
void					load_img(t_envg *e, int img);
void					get_img(t_mlx *mlx, t_mlx *img, char *str);

/*
** interface_initialisation.c
*/
void					init_envg(t_envg *e, t_env *env);
void					init_mlx(t_envg *e);
void					init_pos_value(t_envg *e);
void					init_line_pos(t_envg *e);

/*
** interface_tab.c
*/
int						add_tab(t_envg *e);
int						conf_tab(t_envg *e);
void					home_tab(t_envg *e);
void					del_tab(t_envg *e);

/*
** interface_tab_2.c
*/
void					conf_tab3(t_envg *e, int i);
void					info_tab(t_envg *e);

/*
** interface_tabul.c
*/
void					switch_tabul(t_envg *e);

/*
** interface_creat_obj.c
*/
void					creat_elem(t_envg *e);
void					creat_cam(t_envg *e);
t_parse_obj				*srch_obj(t_envg *e, int id);
t_parse_light			*srch_light(t_envg *e, int id);
void					ft_creat_lst_obj(t_envg *e);

/*
** interface_creat_obj2.c
*/
t_parse_obj				*srch_obj(t_envg *e, int id);
t_parse_light			*srch_light(t_envg *e, int id);
void					reset_line(char **line);
t_light					new_light(t_envg *e);
t_obj					new_obj(t_envg *e);

/*
**interface_selection_add.c
*/
int						select_add(t_envg *e, int x, int y);

/*
** interface_selection_conf.c
*/
int						select_conf2(t_envg *e, int x, int y);

/*
** interface_selection_conf_2.c
*/
int						select_conf(t_envg *e, int x, int y);

/*
** interface_selection_del_home_info.c
*/
int						select_del(t_envg *e, int x, int y);
int						select_info(t_envg *e, int x, int y);
int						select_home(t_envg *e, int x, int y);
int						srch_id(t_envg *e, int pos);

/*
** interface_put_img.c
*/
void					put_img(t_envg *e, int img);

/*
** interface_put_img_2.c
*/
void					put_img4(t_envg *e);
void					put_img5_2(t_envg *e);
void					put_img5(t_envg *e);

/*
** interface_put_img_3.c
*/
void					put_img6(t_envg *e);
void					put_img7(t_envg *e);
void					put_img8(t_envg *e);
/*
** interface_graphic.c
*/
void					graphic_interface(t_envg *scene);
void					re_init_tab(t_envg *e);
void					run_first(t_envg *e);

/*
** interface_check_obj.c
*/
int						check_var_obj(char **def);

/*
** interface_check_obj2.c
*/
void					check_new_obj(t_envg *e, t_obj *obj);
int						sphere_check(char **def);
int						circ_check(char **def);
int						plane_check(char **def);
int						cyl_check(char **def);

/*
** interface_error.c
*/
int						error_gestion(t_envg *e, int x, int y);

/*
** interface_save_img.c
*/
int						bmp_save_img(t_envg *e);

/*
**	/parcer/parser_*.c
*/

void					get_camera3(t_envg *e);
void					increase_l_obj(t_envg *e);
void					ft_get_image_texture(t_envg *e);
void					free_space(char *line, int *x);
int						get_string(char *line, int *x, char **str);
int						get_number(char *line, int *x);
void					add_obj2(char *line, int *x, t_envg *e, int type);
int						add_obj2_2(t_envg *e, int group, char *line, int *x);
void					add_obj2_3(t_envg *e, char *line, int *x, char *rez);
void					get_texture(char *line, int *x, t_envg *e);
int						get_texture_2(t_envg *e, int y, char *path);
void					add_obj22(char *line, int *x, t_envg *e, char *rez);
void					add_obj22_2(t_envg *e, int *x, int y, char *line);
void					add_obj23(char *line, int *x, t_envg *e, char *rez);
void					add_obj23_2(t_envg *e, int *x, int y, char *line);
void					add_obj24(char *line, int *x, t_envg *e, char *rez);
t_vector				get_t_vector(char *line, int *x, int norme);
t_color2				get_t_color(char *line, int *x);
int						get_object(char *line, int *x, t_envg *e, char *name);
int						get_true(char *line, int *x);
int						get_false(char *line, int *x);
int						get_null(char *line, int *x);
void					parse_json(char *line, t_envg *e);
int						count_object(char *line);
void					ft_parse_j(char *name, t_envg *e);
void					exit_error(char *str);
void					get_camera(char *line, int *x, t_envg *e);
double					ft_for_atof(char *line, int y, int x);
void					get_ambient(char *line, int *x, t_envg *e);
void					get_light(char *line, int *x, t_envg *e);
void					get_image_size(char *line, int *x, t_envg *e);
void					ft_parse_json(char *line, t_envg *e);

void					save_scene(t_envg *e, char *id, int fd);
int						save_light_and_cam(t_envg *e, int fd,
	t_parse_light *light);
void					copy_square(t_obj obj, int fd, t_envg *e);
void					copy_cube(t_obj obj, int fd, t_envg *e);
void					copy_sphere(t_obj obj, int fd, t_envg *e);
void					copy_plan(t_obj obj, int fd, t_envg *e);
void					copy_cylindre(t_obj obj, int fd, t_envg *e);
void					copy_cone(t_obj obj, int fd, t_envg *e);
void					copy_circle(t_obj obj, int fd, t_envg *e);
void					copy_rgb(t_obj obj, int fd);
void					copy_pos(t_obj obj, int fd);

t_color2				get_pixel(t_three *bra, t_color2 pix, t_env_cl *e,
	t_g_pix n);
double					get_l_pix(t_three *branch, t_l_obj *tab_light,
	t_obj *l_obj, char flag);
void					free_branch(t_three *branch);
void					*run_rt(void *env);
void					get_image(t_env *e);
void					get_l_tab(t_env *e);
t_env					*ft_create_tab_env(t_env e, int i);
#endif
