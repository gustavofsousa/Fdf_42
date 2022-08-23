NAME = fdf

CC = cc

CFLAGS = -Wextra -Wall -Werror

SRCS = main_backblue.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) -g $(CFLAGS) -Imlx -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS)
	make -s -C mlx
	$(CC) $(OBJS) -g -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)




clean:
	rm -f $(OBJS)
	
