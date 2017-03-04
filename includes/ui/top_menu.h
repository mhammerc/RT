/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_menu.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:09:47 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/03 01:28:57 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOP_MENU_H
# define TOP_MENU_H

# include "widget.h"

typedef struct		s_menu_file
{
	GtkWidget		*menu;
	GtkWidget		*file;
	GtkWidget		*open;
	GtkWidget		*save;
	GtkWidget		*export;
	GtkWidget		*quit;
}					t_menu_file;
#endif
