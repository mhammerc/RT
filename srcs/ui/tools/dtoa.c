/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:05:19 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 12:05:20 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** dtoa (double to alphanumeric) isn't in any standard. So we just trick and
** use printf builtin %f.
*/

char		*dtoa(double value)
{
	char	*output;

	output = (char*)monloc(sizeof(char) * 10);
	snprintf(output, 10, "%f", value);
	return (output);
}
