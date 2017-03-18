#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;

	str = NULL;
	j = 0;
	i = 0;
	if (!(s))
		return (str);
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (s[j])
		j++;
	j--;
	while (j >= 0 && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	str = ft_strnew((j - i + 1 < 0) ? 1 : j - i + 1);
	if (str)
		str = ft_strncpy(str, &(s[i]), (j - i + 1 < 0) ? 1 : j - i + 1);
	return (str);
}
