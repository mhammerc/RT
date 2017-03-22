/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_panel.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:15:30 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 18:17:33 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEFT_PANEL_H
# define LEFT_PANEL_H

# include "libft.h"

/*
** Object tree
*/
typedef struct			s_tree
{
	GtkWidget			*tree;
	GtkTreeStore		*store;
	GtkTreeViewColumn	*col_el;
	GtkTreeViewColumn	*col_type;
	GtkCellRenderer		*renderer;
}						t_tree;

typedef struct			s_lp_btns
{
	GtkWidget			*button;
	GtkWidget			*add_obj;
	GtkWidget			*add_light;
	GtkWidget			*cpy;
	GtkWidget			*remove;
	GMenu				*type_list;
}						t_lp_btns;

/*
** Left panel & dependancies
*/
typedef struct			s_left_panel
{
	GtkWidget			*lp_box;
	t_tree				tree;
	t_lp_btns			lp_btns;
}						t_left_panel;

void					add_obj_btn(GtkButton *button, gpointer view);
void					add_light_btn(GtkButton *button, gpointer view);
void					ft_lst_cpy(t_list **new, t_list *original);
void					cpy_obj_btn(GtkButton *button, gpointer data);
void					del_obj_btn(GtkButton *button, gpointer data);

#endif
