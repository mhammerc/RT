/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_perlin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 19:07:31 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/22 21:43:02 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "renderer.h"
#include "shared.h"

float			gradient(int i, int j)
{
	float	unit;
	float	grad[8][2];

	unit = 1.0 / sqrt(2);
	grad[0][0] = unit;
	grad[0][1] = unit;
	grad[1][0] = -unit;
	grad[1][1] = unit;
	grad[2][0] = unit;
	grad[2][1] = -unit;
	grad[3][0] = -unit;
	grad[3][1] = -unit;
	grad[4][0] = 1;
	grad[4][1] = 0;
	grad[5][0] = -1;
	grad[5][1] = 0;
	grad[6][0] = 0;
	grad[6][1] = 1;
	grad[7][0] = 0;
	grad[7][1] = -1;
	return (grad[i][j]);
}

float			fade(float nb)
{
	float	t;

	t = nb - (int)nb;
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

unsigned int	get_perm_table(int index)
{
	static unsigned int	perm[256] = {
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
	36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
	234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
	88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
	134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
	230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
	1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
	116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
	124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
	47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
	154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
	108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
	242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
	239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
	50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
	141, 128, 195, 78, 66, 215, 61, 156, 180
	};

	return (perm[index % 256]);
}

float			noise(float x, float y, float res)
{
	int		i;
	int		j;
	int		grad[4];
	float	stuv[4];
	float	smooth[2];

	x /= res;
	y /= res;
	i = (int)x & 255;
	j = (int)y & 255;
	grad[0] = get_perm_table(i + get_perm_table(j)) % 8;
	grad[1] = get_perm_table(i + 1 + get_perm_table(j)) % 8;
	grad[2] = get_perm_table(i + get_perm_table(j + 1)) % 8;
	grad[3] = get_perm_table(i + 1 + get_perm_table(j + 1)) % 8;
	stuv[0] = gradient(grad[0], 0) * (x - (int)x)
			+ gradient(grad[0], 1) * (y - (int)y);
	stuv[1] = gradient(grad[1], 0) * (x - ((int)x + 1))
			+ gradient(grad[1], 1) * (y - (int)y);
	stuv[2] = gradient(grad[2], 0) * (x - (int)x)
			+ gradient(grad[2], 1) * (y - ((int)y + 1));
	stuv[3] = gradient(grad[3], 0) * (x - ((int)x + 1))
			+ gradient(grad[3], 1) * (y - ((int)y + 1));
	smooth[0] = stuv[0] + fade(x) * (stuv[1] - stuv[0]);
	smooth[1] = stuv[2] + fade(x) * (stuv[3] - stuv[2]);
	return (smooth[0] + fade(y) * (smooth[1] - smooth[0]));
}

float			ft_perlin(float x, float y, int res)
{
	float	nb;

	//nb = (noise(fabs(x + 100), fabs(y * 100), res) + 1);
	nb = (noise(fabs(x * 100), fabs(y * 100), res) + 1);
	return (nb);
}
