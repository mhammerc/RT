/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:36:57 by aditsch           #+#    #+#             */
/*   Updated: 2017/03/23 10:36:58 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

enum e_object_type	p_str_to_type(char *str)
{
	if (ft_strncmp(str, "SPHERE", 6) == 0)
		return (SPHERE);
	else if (ft_strncmp(str, "PLANE", 5) == 0)
		return (PLANE);
	else if (ft_strncmp(str, "DISK", 4) == 0)
		return (DISK);
	else if (ft_strncmp(str, "CONE", 4) == 0)
		return (CONE);
	else if (ft_strncmp(str, "CYLINDER", 8) == 0)
		return (CYLINDER);
	else if (ft_strncmp(str, "TORUS", 5) == 0)
		return (TORUS);
	else if (ft_strncmp(str, "CSG", 3) == 0)
		return (CSG);
	else if (ft_strncmp(str, "POLYGONS", 8) == 0)
		return (POLYGONS);
	else if (ft_strncmp(str, "EMPTY", 5) == 0)
		return (EMPTY);
	else if (ft_strncmp(str, "LIGHT", 5) == 0)
		return (LIGHT);
	return (EMPTY);
}

size_t				count_tab(char *ln)
{
	size_t	i;

	i = 0;
	while (ln[i] && ln[i] == '\t')
		++i;
	return (i);
}

void				ft_puterr(int err, t_env *env)
{
	t_ui			*ui;
	int				check_first_err;
	GtkDialogFlags	flags;
	GtkWidget		*dialog;

	ui = get_interface();
	check_first_err = 0;
	if (env->error_text[0] != '\0')
		check_first_err = 1;
	if (check_first_err != 0)
		return ;
	if (err == ERR_FILE_OPEN)
		ft_strcpy(env->error_text, "Error : could not open this file");
	flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog = gtk_message_dialog_new(GTK_WINDOW(ui->window), flags,
			GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s\n", env->error_text);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
