/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 10:13:31 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/24 16:17:15 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "ui.h"

typedef struct		s_faces_components
{
	size_t			n_sommets;
	size_t			n_textures;
	size_t			n_normales;
	size_t			n_faces;
	t_vec3			*sommets;
	t_vec2			*textures;
	t_vec3			*normales;
}					t_faces_components;

t_object			*parse_wavefront_file(char *filename);
void				strsplit_free(char **split);

int					count_components_line(char **line, ssize_t ret,
		t_faces_components *components);
int					count_components(char *filename,
		t_faces_components *components);
void				prepare_components(t_faces_components *components);
void				free_components(t_faces_components *components);
int					copy_position(t_object *object,
		t_faces_components *components, char **split);
int					copy_texture(t_faces_components *components, char **split);
int					copy_normales(t_faces_components *components, char **split);
int					copy_components2(t_object *object,
		t_faces_components *components, char **split);
int					copy_components(t_object *object, char *filename,
		t_faces_components *components);
void				init_faces(t_object *object,
		t_faces_components *components);
int					copy_one_face2(t_face *face, t_faces_components *components,
		char **split);
int					copy_one_face(t_object *object,
		t_faces_components *components, char **split);
int					copy_faces(t_object *object, char *filename,
		t_faces_components *components);
int					start_parsing(t_object *object, char *filename);

#endif
