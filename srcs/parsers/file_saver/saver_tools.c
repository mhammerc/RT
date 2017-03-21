#include "file_saver.h"

void	print_vec3(FILE *file, char *key, t_vec3 value, char *tab)
{
	fprintf(file, "%s\t%s: %.1f; %.1f; %.1f\n", tab, key,
		value.x, value.y, value.z);
}

char	*str_tab(int depth)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * (depth + 1));
	str[depth] = 0;
	ft_memset(str, '\t', depth);
	return (str);
}
