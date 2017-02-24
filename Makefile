NAME = rt

SRCS = srcs/main.c \
	   srcs/scene_manager.c \
	   srcs/interface.c

RESOURCES = srcs/kernels/kernel.cl \
			srcs/interface/rt_glade.glade

OBJS = $(SRCS:.c=.o)

GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS = $(shell pkg-config --libs gtk+-3.0)

CC = gcc

CFLAGS = -Wall -Werror -Wextra
CFLAGS += $(GTK_CFLAGS)

CLIBS = -framework OpenCL
CLIBS += $(GTK_CLIBS)

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(CLIBS) $(OBJS)
	-mkdir resources
	cp $(RESOURCES) resources

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	-rm -rf resources

re: fclean all
