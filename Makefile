NAME		=	rt

SRCS_PATH	=	srcs

SRCS_NAME	=	main.c										\
				renderer/compute_image.c					\
				renderer/camera.c							\
				renderer/maths/vec3_norm.c					\
				renderer/maths/vec3_op.c					\
				renderer/maths/solve.c						\
				renderer/maths/solve_quad.c					\
				renderer/objects/sphere.c					\
				renderer/objects/polygon.c					\
				renderer/objects/torus.c					\
				renderer/objects/cylinder.c					\
				renderer/objects/cone.c						\
				renderer/objects/plane.c					\
				renderer/objects/disk.c					\
				renderer/objects/csg.c						\
				renderer/objects/object_selection.c			\
				ui/create_object.c							\
				ui/display_panel.c							\
				ui/left_panel/add_buttons.c					\
				ui/left_panel/left_panel.c					\
				ui/obj_tree.c								\
				ui/right_panel/selected_el_properties.c		\
				ui/right_panel/cam_properties.c				\
				ui/right_panel/right_panel.c				\
				ui/right_panel/scene_properties.c			\
				ui/right_panel/color_chooser.c				\
				ui/tools/dtoa.c								\
				ui/tools/type_char.c						\
				ui/menu_keys.c								\
				ui/realtime_keys.c							\
				ui/widgets/numeric_entry.c					\
				ui/widgets/scale_entry.c					\
				ui/widgets/text_entry.c						\
				ui/widgets/vector3_entry.c					\
				ui/window.c									\
				ui/ui_print_scene.c							\
				ui/top_menu/top_menu.c						\
				file_loader/file_loader.c					\
				file_loader/parser.c						\
				file_loader/object.c						\
				file_loader/camera.c						\
				file_loader/tools.c							\
				file_loader/vec3.c							\
				converter/converter.c						\
				obj_parser/obj_parser.c						\
				texture_loader/texture_loader.c				\

OBJS_NAME 	= 	$(SRCS_NAME:.c=.o)

OBJS_PATH	=	./objs
INCS_PATH	=	./includes
LFT_PATH	=	./libs/libft

GTK_CFLAGS	=	$(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS	=	$(shell pkg-config --libs gtk+-3.0)

CC			=	gcc -fdiagnostics-color=auto

CFLAGS		=	-g -I$(LFT_PATH) -I$(INCS_PATH) -I$(INCS_PATH)/ui -I$(INCS_PATH)/renderer -I$(INCS_PATH)/converter -I$(INCS_PATH)/obj_parser -I$(INCS_PATH)/texture_loader -Wall -Wextra
CFLAGS		+=	$(GTK_CFLAGS)

CLIBS		=	-lm -lpthread -L$(LFT_PATH) -lft
CLIBS		+=	$(GTK_CLIBS)

SRCS		=	$(addprefix $(SRCS_PATH)/,$(SRCS_NAME))
OBJS		=	$(addprefix $(OBJS_PATH)/,$(OBJS_NAME))

all: $(NAME)

$(NAME): 		create_objs_dir $(OBJS)
				make -C $(LFT_PATH)
				gcc $(OBJS) -o $@ $(CLIBS)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
				$(CC) -o $@ -c $< $(CFLAGS)

create_objs_dir:
				@mkdir $(OBJS_PATH) 2> /dev/null || true
				@mkdir $(OBJS_PATH)/converter 2> /dev/null || true
				@mkdir $(OBJS_PATH)/renderer 2> /dev/null || true
				@mkdir $(OBJS_PATH)/renderer/maths 2> /dev/null || true
				@mkdir $(OBJS_PATH)/renderer/objects 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/left_panel 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/right_panel 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/tools 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/widgets 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/top_menu 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/top_menu/file_saver 2> /dev/null || true
				@mkdir $(OBJS_PATH)/file_loader 2> /dev/null || true
				@mkdir $(OBJS_PATH)/obj_parser 2> /dev/null || true
				@mkdir $(OBJS_PATH)/texture_loader 2> /dev/null || true

clean:
				rm -rf $(OBJS)
				@rm -rf $(OBJS_PATH) 2> /dev/null || true
				make -C $(LFT_PATH) clean

fclean:
				rm -rf $(OBJS)
				rm -rf $(NAME)
				@rm -rf $(OBJS_PATH) 2> /dev/null || true
				make -C $(LFT_PATH) fclean

re: 			fclean all
