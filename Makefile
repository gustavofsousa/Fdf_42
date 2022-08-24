NAME = fdf

CC = cc

CFLAGS = -Wextra -Wall -Werror

SRCS = main_backblue.c

INC = ./include/libft_42/libft.h \
	  ./include/get_next_line_42/get_next_line.h \
	  ./fdf.h

OBJS = $(SRCS:.c=.o)

LIBXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit 

%.o: %.c
	$(CC) -g $(CFLAGS) -Imlx -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS)
	make -s -C mlx
	make -C include/libft_42
	$(CC) $(OBJS) $(LIBXFLAGS) -o $(NAME)

re: clean all

clean:
	rm -f $(OBJS)

fclean: clean
	
