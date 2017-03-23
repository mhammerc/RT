/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_saver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racousin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:13:18 by racousin          #+#    #+#             */
/*   Updated: 2017/03/23 10:13:20 by racousin         ###   ########.fr       */
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
