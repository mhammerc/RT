/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_saver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:13:18 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/24 16:17:04 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_SAVER_H
# define FILE_SAVER_H

# include "ui.h"
# include "right_panel.h"

char	*get_enum_type(enum e_object_type type);
void	print_vec3(FILE *file, char *key, t_vec3 value, char *tab);
char	*str_tab(int depth);

#endif
