typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	void				*data;
	int					bpp;
	int					sizeline;
	int					endian;
	int					w;
	int					h;
	int					crenelage;
	double				vide;
}						t_mlx;

typedef	struct			s_obj
{
	double				angle;
	double				radius;
	double				ind_refrac; // 1 -> +
	double				ind_reflec; // 0 -> 1
	double4				pos;
	double4				dir;
	double4				point;
	double				ind_transp; //0 -> 1
	unsigned short int	group;
	unsigned char		negatif;
	unsigned char		vide;
	void				*name;
	uchar4				color;
	unsigned short int	id;
	unsigned char		type;
	unsigned char		id_texture;
}						t_obj;

typedef struct			s_light
{
	double4				pos;
	uchar4				color;
	double				vide;
	double				vide2;
	void				*name;
}						t_light;

typedef struct			s_l_obj
{
	int 				id;
	double				p_hit_x;
	double				p_hit_y;
	double				p_hit_z;
}						t_l_obj;

typedef struct			s_env_cl
{
	__global t_l_obj	*lst;
	__global uchar4		*color_lst;
	__global t_light	*light;
	__global t_obj		*l_obj;
	__global t_mlx		*texture;
	int					nb_obj;
	int					nb_light;
	void				*cl;
	int					group_max;
	int 				amb;
}						t_env_cl;

# define T 2000000

double			ft_clamp_min(double a, double b);
double			ft_clamp_max(double a, double b);
double			ft_clamp(double a, double b, double c);

double4			vsub(double4 a, double4 b);
double4			new_v(double x, double y, double z);
double4			vadd(double4 a, double4 b);
double4			vhit(double4 pos, double4 dir, double dist);
double4			vrot(double4 u, double angle, double4 point);
double4			vcross(double4 a, double4 b);
double4			vmult(double4 a, double4 b);
double4			vmult_dbl(double4 a, double b);
double4			vnorm(double4 a);
double			vpscal(double4 a, double4 b);
double4 		vcross_prod(double4 a, double4 b);
double			vsize(double4 v);

double2			solve_quad(double a, double b, double c, int *toucher);
double2			inter_sphere(t_obj sp, double4 o, double4 dir, int *toucher);
double2			inter_plane(t_obj p, double4 o, double4 dir, int *toucher);
double2			inter_circle(t_obj p, double4 o, double4 dir, int *toucher);
double2			inter_square(t_obj p, double4 o, double4 dir, int *toucher);
double2			inter_cylinder(t_obj cyl, double4 o, double4 dir, int *toucher);
double2			inter_cone(t_obj cone, double4 o, double4 dir, int *toucher);

double4			ft_angle_sphere(t_obj s, double4 hit);
double4			ft_angle_plane(t_obj p);
double4			ft_angle_circle(t_obj p);
double4			ft_angle_square(t_obj p);
double4			ft_angle_cylinder(t_obj obj, double4 p_hit);
double4			ft_angle_cone(t_obj obj, double4 p_hit);

uchar4			get_color(__global t_mlx *texture, double4 p_hit, t_obj obj);
t_obj			inter_obj_light(__global t_env_cl *e, double4 p_ray, double4 v_ray, int *tab_obj_light_id, double *tab_obj_light_t);
uchar4			l_shine(uchar4	 , uchar4	 olor, double angle, double t);
uchar4			add_light(__global t_env_cl *e, uchar4	 ixel, double4 p_hit, t_obj obj, __global t_mlx *texture, int index);
uchar4			ft_start( __global t_env_cl *e, __global t_obj *lst_obj, t_l_obj lst);
void			ft_create_tab_obj_light(__global t_env_cl *e, int id, double2 tr, int *tab_obj_light_id, double *tab_obj_light_t, int part2);
