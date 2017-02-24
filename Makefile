NAME = rt

SRCS = srcs/main.c \
	   srcs/scene_manager.c \
	   srcs/interface.c

RESOURCES = srcs/kernels/kernel.cl \
			srcs/interface/rt_glade.glade \
			srcs/env.h

OBJS = $(SRCS:.c=.o)

GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS = $(shell pkg-config --libs gtk+-3.0)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Ilibs/libft
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
