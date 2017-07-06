
#include "../includes/interface_rt.h"

void			info_tab(t_envg *e)
{
	int save;
	int i;

	load_img(e, 5);
	e->volet = (t_tab_valid){0, 0, 0, 0, 1};
	i = 1;
	save = e->pos;
	while (i <= 2)
	{
		e->pos = i;
		load_img(e, e->pos_value[i]);
		print_line(e, i + 40, 30);
		i++;
	}
	put_img6(e);
	e->pos = save;
}