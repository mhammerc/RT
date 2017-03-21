#ifndef PARSER_H
# define PARSER_H

# include "shared.h"
# include <libft.h>

/*
** New
*/
typedef struct			s_parser_cam
{
	t_vec3				pos;
	t_vec3				look_at;
	t_vec3				up;
}						t_parser_cam;


typedef struct			s_env
{
	t_parser_cam		camera;
	t_list				*objects;
	t_list				**current_object;
	size_t				depth;

	char				*ln;

	int					fd;

	int					object_type;

	char				error_text[80];
}						t_env;

t_vec3					p_read_vec3(t_env *env, char *ln);
void					p_parse_object(t_env *env, char *ln);
void					p_parse_camera(t_env *env, char *ln);
enum e_object_type		p_str_to_type(char *str);
size_t					count_tab(char *ln);


/*
** Old
*/
# define MAX_INDEX_SCENE 2
# define MAX_INDEX_CAMERA 2
# define MAX_INDEX_OBJECT 6

enum	e_env
{
	UNDEFINED,
	SCENE,
	CAMERA,
	OBJECT,
	GROUP
};

enum	e_errors
{
	ERR_FILE_OPEN,
	ERR_FILE_SYNTAX,
	ERR_NO_ENTITY,
	ERR_UNKNOWN_OBJ,
	ERR_WRONG_ARGS
};

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_parser_scene
{
	char				*name;
	t_point				size;
}						t_parser_scene;

typedef struct			s_entity
{
	enum e_env			env_type;
	enum e_object_type	type;
	t_vec3				pos;
	t_vec3				rot;
	t_vec3				color;
	double				length;
	double				radius;
	double				kdiff;
	double				kspec;
	char				name[80];
}						t_entity;


typedef struct			s_entity_lst
{
	t_entity			entity;
	struct s_entity_lst	*next;
}						t_entity_lst;

typedef struct			s_group_lst
{
	t_entity_lst		*group;
	struct s_group_lst	*next;
}						t_group_lst;
int						ft_exit(void);
int						ft_check_all(t_env *env);
int						ft_check_entity(t_env *env, int entity_type);
void					ft_puterr(int err, t_env *env);
void					ft_init_tabs(t_env *env);
void					ft_init_struct(t_env *env);
void					ft_read_file(char *name, t_env *env);
void					ft_reset(t_env *env, int entity_type);
void					ft_free_split(char **tab);
void					ft_free_list(t_entity_lst **entity_lst);
void					ft_fill_scene(t_env *env, char *ln);
void					ft_fill_scene_size(t_env *env, char **tab);
void					ft_fill_scene_name(t_env *env, char **tab);
void					ft_fill_camera(t_env *env, char *ln);
void					ft_fill_camera_position(t_env *env, char **tab);
void					ft_fill_camera_direction(t_env *env, char **tab);
void					ft_fill_camera_rotation(t_env *env, char **tab);
void					ft_fill_object_color(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_type(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_size(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_radius(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_length(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_kspec(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_kdiff(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_name(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_position(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_object_rotation(t_env *env, char **tab,
							t_entity *entity);
void					ft_fill_spots(t_env *env, char *ln);
t_entity_lst			*ft_cpy_lst(t_entity_lst *entity_lst);
t_entity_lst			*ft_new_entity(t_entity entity);
void					ft_push_entity(t_entity_lst **entity_lst,
							t_entity_lst *new);
t_group_lst				*ft_new_group(t_entity_lst *entity_lst);
void					ft_push_group(t_group_lst **group_lst,
							t_group_lst *new);
void					ft_fill_env(t_env *env, char *ln);
void					ft_fill_group(t_env *env, char *ln);
void					ft_fill_object_group(t_env *env, char *ln);
int						ft_count_tabs(const char *s);

#endif
