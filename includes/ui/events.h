/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:03:41 by gpoblon           #+#    #+#             */
/*   Updated: 2017/03/22 18:13:13 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

void			event_handler_window(t_ui *ui);
int				on_key_press_window(GtkWidget *widget, GdkEventKey *event,
															gpointer user_data);
void			event_handler_display(t_ui *ui);
int				on_key_press_display(GtkWidget *widget, GdkEventKey *event,
															gpointer user_data);

#endif
