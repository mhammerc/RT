#include "view.h"

/*
** dtoa (double to alphanumeric) isn't in any standard. So we just trick and
** use printf builtin %f.
*/

char		*dtoa(double value)
{
	char	*output;

	output = (char*)malloc(sizeof(char) * 10);
	snprintf(output, 5, "%f", value);
	return (output);
}
