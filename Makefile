NAME = fdf

CC = cc

CFLAGS = -Wextra -Wall -Werror

SRCS = main.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS)
	make -s -C mlx
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)




clean:
	rm -f $(OBJS)
	
