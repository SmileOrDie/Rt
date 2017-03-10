typedef	struct			s_obj
{
	int					type;
	int					id;
	double				vide2;
	double				vide3;
	double				vide4;
	double4				pos;
	double4				dir;
	double4				point;
	double				radius;
	double				angle;
	int4				color;
	double				t;
	double				ind_refrac; // 1 -> +
	double				ind_reflec; // 0 -> 1
	double				ind_transp; //0 -> 1
}						t_obj;

typedef struct			s_light
{
	double4				pos;
	double4				color;
	// double				angle;
	// double				vide;
	// double				vide2;
	// double				vide3;
	// double4				norm;
}						t_light;

typedef struct			s_cam
{
	double4				eye;
	double4				l_at;
	double4				up;
	double				dist;
	double				fov;
	double				h;
	double				w;
	double4				c;
	double4				l;
	double4				n;
	double4				u;
}						t_cam;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	int					bpp;
	int					sizeline;
	int					endian;
	int					w;
	int					h;
	int					crenelage;
}						t_mlx;

typedef struct			s_env
{
	__global t_mlx		*mlx;
	__global t_light	*light;
	__global t_obj		*l_obj;
	t_obj				*tab_transp;
	t_obj				*tab_transp_l;
	void				*vide;
	void				*vide2;
	__global t_cam		*cam;
	__global t_obj		obj;
	double4				norm;
	int4				c_hit;
	int					flag;
	double				amb;
	double				angle;
	int					r;
	int					g;
	int					b;
	int					nb_obj;
	int					nb_light;
	double				move;
	double				truc1;
	double				truc2;
	void				*cl;
}						t_env;

# define T 2000000

double			ft_clamp_min(double a, double b);
double			ft_clamp_max(double a, double b);
double			ft_clamp(double a, double b, double c);

double4			vsub(double4 a, double4 b);
double4			new_v(double x, double y, double z);
double4			vadd(double4 a, double4 b);
double4			vhit(double4 pos, double4 dir, double dist);
double4			vmult(double4 a, double4 b);
double4			vmult_dbl(double4 a, double b);
double4			vnorm(double4 a);
double			vpscal(double4 a, double4 b);
double			vsize(double4 v);

double			solve_quad(double a, double b, double c);
double			inter_sphere(t_obj sp, double4 o, double4 dir);
double			inter_plane(t_obj p, double4 o, double4 dir);
double			inter_cylinder(t_obj cyl, double4 o, double4 dir);
double			inter_cone(t_obj cone, double4 o, double4 dir);

void			ft_angle_sphere(t_obj s, double4 hit, double4 dir_l, t_light light, __global t_env *e);
void			ft_angle_plane(t_obj p, double4 dir_l, t_light light, __global t_env *e);
void			ft_angle_cylinder(t_obj obj, double4 p_hit, double4 l_vector, t_light light, __global t_env *e);
void			ft_angle_cone(t_obj obj, double4 p_hit, double4 l_vector, t_light light, __global t_env *e);

int4			put_pixel(int x, int y, __global t_env *e);

void			ft_create_tab_transp(__global t_env *e, t_obj obj, double tr);
void			inter_obj(__global t_env *e, double4 pos, double4 dir);
int4			l_color(int4 c, int4 color,__global t_env *e);
int4			add_light(__global t_env *e, double t, double4 phit, int ct, int4 color);
void			ft_raytracer3(__global t_env *e, double transp, double t);
void			ft_raytracer2(__global t_env *e, int count, double4 dir);
int4			ft_raytracer(int x, int y,__global t_env *e, int4 pixel);

void			ft_start_ray(__global char *data, __global t_env *e, int x, int y);

