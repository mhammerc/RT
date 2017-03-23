/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saver_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:37:15 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/23 10:37:16 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_saver.h"

void	print_vec3(FILE *file, char *key, t_vec3 value, char *tab)
{
	fprintf(file, "%s\t%s: %f; %f; %f\n", tab, key,
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
