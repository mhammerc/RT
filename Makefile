NAME = rt

SRCS = main.c

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

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all
