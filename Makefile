NAME = rt

SRCS = srcs/main.c			\
	   srcs/renderer/compute_image.c	\
	   srcs/renderer/camera.c		\
	   srcs/renderer/maths/vec3_norm.c		\
	   srcs/renderer/maths/vec3_op.c		\
	   srcs/renderer/init.c \
	   srcs/renderer/singleton.c \
	   srcs/renderer/opencl_tools.c \
	   srcs/ui/create_object.c	\
	   srcs/ui/display_panel.c	\
	   srcs/ui/left_panel/add_buttons.c     	\
	   srcs/ui/left_panel/left_panel.c     	\
	   srcs/ui/obj_tree.c     	\
	   srcs/ui/right_panel/selected_el_properties.c    	\
	   srcs/ui/right_panel/cam_properties.c    	\
	   srcs/ui/right_panel/right_panel.c    	\
	   srcs/ui/right_panel/scene_properties.c    	\
	   srcs/ui/tools/dtoa.c          	\
	   srcs/ui/tools/type_char.c     	\
	   srcs/ui/top_menu.c     	\
	   srcs/ui/widgets/numeric_entry.c        	\
	   srcs/ui/widgets/scale_entry.c        	\
	   srcs/ui/widgets/text_entry.c        	\
	   srcs/ui/widgets/vector3_entry.c        	\
	   srcs/ui/window.c						\
	   srcs/ui/ui_print_scene.c \
	   srcs/converter/gtk2cl.c

RESOURCES = srcs/renderer/kernels/kernel.cl	\
			srcs/renderer/kernels/sphere.cl \
			srcs/renderer/kernels/quadratic_equations.cl \
			srcs/renderer/kernels/objects.cl \
			srcs/renderer/kernels/raytracer.h \
			includes/renderer/shared.h

OBJS = $(SRCS:.c=.o)

GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS = $(shell pkg-config --libs gtk+-3.0)

CC = gcc

CFLAGS = -g -Ilibs/libft -Iincludes -Iincludes/ui -Iincludes/renderer -Iincludes/converter
CFLAGS += $(GTK_CFLAGS)

CLIBS = -lm -Llibs/libft -lft
CLIBS += $(GTK_CLIBS)

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	CLIBS += -framework OpenCL
endif

ifeq ($(UNAME),Linux)
	CLIBS += -lOpenCL
endif

all: $(NAME)

$(NAME): copy_resources $(OBJS)
	make -C libs/libft
	gcc -o $(NAME) $(OBJS) $(CLIBS)

copy_resources:
	-mkdir resources
	cp $(RESOURCES) resources

clean:
	rm -rf $(OBJS)
	make -C libs/libft clean

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
	rm -rf resources
	make -C libs/libft fclean

re: fclean all
