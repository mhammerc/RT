#include "ui.h"
#include "right_panel.h"

// Saver
void	save_cam_properties(FILE * file);

void	save_cam_properties(FILE *file)
{
	t_ui		*ui;
	t_ui_cam	*cam;

	ui = get_interface();
	cam = ui->cam;
	fprintf(file, "camera:\n");
	fprintf(file, "\tposition: %.1lf; %.1lf; %.1lf\n", cam->pos.x,
														cam->pos.y,
														cam->pos.z);
	fprintf(file, "\tdirection: %.1lf; %.1lf; %.1lf\n", cam->dir.x,
														cam->dir.y,
														cam->dir.z);
	fprintf(file, "\n");
}

void	save_elements_properties(FILE *file, t_list *obj)
{
	static int depth = -1;

	++depth;
	while (obj)
	{
		printf("name = %s, %d\n", ((t_object *)obj->content)->name, depth);
		if (obj->children)
		{
			save_elements_properties(file, obj->children);
		}
		obj = obj->next;
	}
	--depth;
	// while (obj)
	// {
	// 	t_object *object = obj->content;
	// 	jfkdsjfklsdjflksdjflkjsdflkj
	// 	if (obj->children)
	// 		save_elements_properties(obj->children);
	// 	obj = obj->next;
	// }

	// else if (obj->children)
	// {
	// 	printf("name children = %s\n", ((t_object *)obj->children->content)->name);
	// 	save_elements_properties(file, obj->children->next);
	// }
	// else
	// 	printf("name parent = %s\n", ((t_object *)obj->content)->name);
	// save_elements_properties(file, obj->next);

	// if (obj)
	// {
	// 	printf("name parent = %s\n", ((t_object *)obj->content)->name);
	// 	save_elements_properties(file, obj->next);
		// if (obj->children)
		// {
		// 	save_elements_properties(file, obj->children->next);
		// 	printf("name children = %s\n", ((t_object *)obj->children->content)->name);
		// }
	// }
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
		save_elements_properties(file, ui->objs);
		fclose(file);
	}
	else
		printf("Impossible d'ouvrir le fichier %s\n", filename);
}
