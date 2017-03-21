#include "file_loader.h"

static int		p_is_digit(char c)
{
	return ((c >= '0' && c <= '9') || c == '.' || c == '-');
}

t_vec3			p_read_vec3(char *ln)
{
	t_vec3	v;
	size_t	i;

	i = 0;
	while (ln[i] && !p_is_digit(ln[i]))
		++i;
	v.x = atof(ln + i);
	while (ln[i] && p_is_digit(ln[i]))
		++i;
	while (ln[i] && !p_is_digit(ln[i]))
		++i;
	v.y = atof(ln + i);
	while (ln[i] && p_is_digit(ln[i]))
		++i;
	while (ln[i] && !p_is_digit(ln[i]))
		++i;
	v.z = atof(ln + i);
	return (v);
}
