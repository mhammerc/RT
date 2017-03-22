#include "file_saver.h"

static void		save_cam_properties(FILE *file)
{
	t_ui		*ui;
	t_ui_cam	*cam;

	ui = get_interface();
	cam = ui->cam;
	fprintf(file, "camera:\n");
	print_vec3(file, "position", cam->pos, "");
	print_vec3(file, "lookAt", cam->dir, "");
	print_vec3(file, "up", cam->up, "");
	fprintf(file, "\n");
}

static void		save_obj(FILE *file, t_object *obj, int depth)
{
	char	*tab;

	tab = str_tab(depth);
	fprintf(file, "%sobject:\n", tab);
	fprintf(file, "%s\ttype: %s\n", tab, get_el_type_char(obj));
	fprintf(file, "%s\tname: %s\n", tab, obj->name);
	print_vec3(file, "position", obj->pos, tab);
	print_vec3(file, "rotation", obj->rot, tab);
	print_vec3(file, "color", obj->color, tab);
	fprintf(file, "%s\tradius: %f\n", tab, obj->radius);
	fprintf(file, "%s\tlength: %f\n", tab, obj->length);
	fprintf(file, "%s\tkspec: %f\n", tab, obj->kspec);
	fprintf(file, "%s\tkdiff: %f\n", tab, obj->kdiff);
	fprintf(file, "%s\ttransmittance: %f\n", tab, obj->transmittance);
	fprintf(file, "%s\treflectance: %f\n", tab, obj->reflectance);
	fprintf(file, "%s\trindex: %f\n", tab, obj->rindex);
	fprintf(file, "%s\tcsgOperation: %c\n", tab, obj->operation);
	if (obj->filename)
		fprintf(file, "%s\tfile: %s\n", tab, obj->filename);
	fprintf(file, "%s\ttexture: %d\n", tab, obj->have_texture);
	if (obj->texture_filename)
		fprintf(file, "%s\ttexture_filename: %s\n", tab, obj->texture_filename);
	fprintf(file, "\n");
	free(tab);
}

static void		save_elements_properties(FILE *file, t_list *obj, int depth)
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

void			save_scene(char *filename)
{
	FILE	*file;
	t_ui	*ui;

	file = NULL;
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
