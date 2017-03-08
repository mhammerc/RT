NAME		=	rt

SRCS_PATH	=	srcs

SRCS_NAME	=	main.c										\
				renderer/compute_image.c					\
				renderer/camera.c							\
				renderer/maths/vec3_norm.c					\
				renderer/maths/vec3_op.c					\
				renderer/init.c								\
				renderer/singleton.c						\
				renderer/opencl_tools.c						\
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
				ui/top_menu.c								\
				ui/keymapping.c								\
				ui/widgets/numeric_entry.c					\
				ui/widgets/scale_entry.c					\
				ui/widgets/text_entry.c						\
				ui/widgets/vector3_entry.c					\
				ui/window.c									\
				ui/ui_print_scene.c							\
				converter/gtk2cl.c							\

RESOURCES	=	srcs/renderer/kernels/kernel.cl					\
				srcs/renderer/kernels/sphere.cl					\
				srcs/renderer/kernels/plan.cl					\
				srcs/renderer/kernels/quadratic_equations.cl	\
				srcs/renderer/kernels/objects.cl				\
				srcs/renderer/kernels/raytracer.h				\
				includes/renderer/shared.h

OBJS_NAME 	= 	$(SRCS_NAME:.c=.o)

OBJS_PATH	=	./objs
INCS_PATH	=	./includes
LFT_PATH	=	./libs/libft

GTK_CFLAGS	=	$(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS	=	$(shell pkg-config --libs gtk+-3.0)

CC			=	gcc

CFLAGS		=	-g -I$(LFT_PATH) -I$(INCS_PATH) -I$(INCS_PATH)/ui -I$(INCS_PATH)/renderer -I$(INCS_PATH)/converter
CFLAGS		+=	$(GTK_CFLAGS)

CLIBS		=	-lm -L$(LFT_PATH) -lft
CLIBS		+=	$(GTK_CLIBS)

SRCS		=	$(addprefix $(SRCS_PATH)/,$(SRCS_NAME))
OBJS		=	$(addprefix $(OBJS_PATH)/,$(OBJS_NAME))

UNAME		:=	$(shell uname)

ifeq ($(UNAME),Darwin)
	CLIBS	+=	-framework OpenCL
endif

ifeq ($(UNAME),Linux)
	CLIBS	+=	-lOpenCL
endif

all: $(NAME)

$(NAME): 		create_objs_dir copy_resources $(OBJS)
				make -C $(LFT_PATH)
				gcc $(OBJS) -o $@ $(CLIBS)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
				$(CC) -o $@ -c $< $(CFLAGS)

create_objs_dir:
				@mkdir $(OBJS_PATH) 2> /dev/null || true
				@mkdir $(OBJS_PATH)/converter 2> /dev/null || true
				@mkdir $(OBJS_PATH)/renderer 2> /dev/null || true
				@mkdir $(OBJS_PATH)/renderer/maths 2> /dev/null || true
				@mkdir $(OBJS_PATH)/renderer/kernels 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/left_panel 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/right_panel 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/tools 2> /dev/null || true
				@mkdir $(OBJS_PATH)/ui/widgets 2> /dev/null || true

copy_resources:
				@mkdir resources 2> /dev/null || true
				cp $(RESOURCES) resources

clean:
				rm -rf $(OBJS)
				@rm -rf $(OBJS_PATH) 2> /dev/null || true
				make -C $(LFT_PATH) clean

fclean:
				rm -rf $(OBJS)
				rm -rf $(NAME)
				@rm -rf $(OBJS_PATH) 2> /dev/null || true
				rm -rf resources
				make -C $(LFT_PATH) fclean

re: 			fclean all
