#include "file_saver.h"

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
