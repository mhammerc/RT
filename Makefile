NAME = rt

SRCS = srcs/main.c			\
	   srcs/compute/scene_manager.c	\
	   srcs/compute/camera.c		\
	   srcs/compute/vec3_norm.c		\
	   srcs/compute/vec3_op.c		\
	   srcs/ui/create_object.c	\
	   srcs/ui/display_panel.c	\
	   srcs/ui/gtk2cl.c       	\
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
	   srcs/ui/ui_print_scene.c

RESOURCES = srcs/compute/kernels/kernel.cl	\
			includes/compute/env.h

OBJS = $(SRCS:.c=.o)

GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS = $(shell pkg-config --libs gtk+-3.0)

CC = gcc

CFLAGS = -g -Ilibs/libft -Iincludes -Iincludes/ui -Iincludes/compute
CFLAGS += $(GTK_CFLAGS)

CLIBS = -framework OpenCL -Llibs/libft -lft
CLIBS += $(GTK_CLIBS)

all: $(NAME)

$(NAME): copy_resources $(OBJS)
	make -C libs/libft
	gcc -o $(NAME) $(CLIBS) $(OBJS)

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
