#include "ui.h"
#include "right_panel.h"

char	*get_enum_type(enum e_object_type type)
{
	static char *list[OBJECT_TYPE_COUNT] = {"SPHERE", "PLANE", "CONE",
		"CYLINDER", "TORUS", "CSG", "POLYGONS", "EMPTY", "LIGHT"};

	return (list[type]);
}

void	print_vec3(FILE *file, char *key, t_vec3 value, char *tab)
{
	fprintf(file, "%s\t%s: %.1lf; %.1lf; %.1lf\n", tab, key,
		value.x, value.y, value.z);
}

char	*str_tab(int depth)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	if (depth == 0)
		return (str);
	str = (char *)malloc(sizeof(char) * depth);
	while (i < depth)
		str[i++] = '\t';
	return (str);
}

void	save_cam_properties(FILE *file)
{
	t_ui		*ui;
	t_ui_cam	*cam;

	ui = get_interface();
	cam = ui->cam;
	fprintf(file, "camera:\n");
	print_vec3(file, "position", cam->pos, "");
	print_vec3(file, "lookAt", cam->dir, "");
	fprintf(file, "\n");
}

void	save_obj(FILE *file, t_object *obj, int depth)
{
	char				*tab;
	enum e_object_type	type;

	tab = str_tab(depth);
	fprintf(file, "%sobject:\n", tab);
	fprintf(file, "%s\ttype: %s\n", tab, get_enum_type(obj->type));
	fprintf(file, "%s\tname: %s\n", tab, obj->name);
	print_vec3(file, "position", obj->pos, tab);
	print_vec3(file, "rotation", obj->rot, tab);
	print_vec3(file, "color", obj->color, tab);
	fprintf(file, "%s\tradius: %lf\n", tab, obj->radius);
	fprintf(file, "%s\tkspec: %lf\n", tab, obj->kspec);
	fprintf(file, "%s\tkdiff: %lf\n", tab, obj->kdiff);
	fprintf(file, "\n");
	free(tab);
}

void	save_elements_properties(FILE *file, t_list *obj, int depth)
{
	++depth;
	while (obj)
	{
		save_obj(file, ((t_object *)obj->content), depth);
		if (obj->children)
			save_elements_properties(file, obj->children, depth);
		obj = obj->next;
	}
	--depth;
}

void	save_scene(char *filename)
{
	FILE	*file = NULL;
	t_ui	*ui;

	ui = get_interface();
	file = fopen(filename, "w+");
	if (file)
	{
		save_cam_properties(file);
		save_elements_properties(file, ui->objs, -1);
		fclose(file);
	}
	else
		printf("Unable to open %s!\n", filename);
}
