/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_rt.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:45:45 by shamdani          #+#    #+#             */
/*   Updated: 2017/06/27 18:25:41 by pde-maul         ###   ########.fr       */
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

typedef struct			s_envg
{
	t_env				*e;
	t_mlx				*mlx;
	t_mlx				img;
	char				**line;
	int					i_lst;
	int					obj;
	int					light;
	t_pos_i				line_pos[LINE_SIZE];
	t_pos_i				img_pos[LINE_SIZE];
	int					pos;
	int					pos_value[LINE_SIZE];
	int					nb_c;
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
	t_tabu				tab_texture;
	t_tabu				tab_scene;
	pthread_t			thread;
}						t_envg;

int						keypress(int key, t_envg *e);
/*
** interface_modify_delete.c
*/
void					modif_light(t_envg *e, int light);
void					modif_list(t_envg *e, int obj);
void					del_elem(t_envg *e, int i);
void					modif_default(t_envg *e);
void					init_id(t_env *e);

/*
** interface_keypress.c
*/
int						interface_keypress(int key, t_envg *e);

/*
** interface_line.c
*/
void					print_line(t_envg *e, int line, int precision);
void					add_line(char *dest, char *src, int f);
void					del_line(t_envg *e);

/*
** interface_mouse.c
*/
int						interface_mouse_click(int button, int x,
						int y, t_envg *e);
void					ft_exit(t_envg *e);

/*
** interface_key_2.c
*/
char					*ft_print_key_6(int key, t_envg *e);

/*
** interface_key.c
*/
char					*ft_print_key(int key, t_envg *e);

/*
** interface_mouse.c
*/
int						mouss_click(int button, int x, int y, t_envg *e);

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
/*
**interface_selection_add.c
*/
int						select_add(t_envg *e, int x, int y);

/*
** interface_selection_conf.c
*/
int						select_conf(t_envg *e, int x, int y);

/*
** interface_selection_del_home_info.c
*/
int						select_del(t_envg *e, int x, int y);
int						select_info(t_envg *e, int x, int y);
int						select_home(t_envg *e, int x, int y);

/*
** interface_put_img.c
*/
void					put_img(t_envg *e, int img);

/*
** interface_graphic.c
*/
void					re_init_tab(t_envg *e);
void					run_first(t_envg *e);

/*
** interface_check_obj.c
*/
int						check_var_obj(char **def);

/*
** interface_error.c
*/
int						error_gestion(t_envg *e, int x, int y);

#endif
