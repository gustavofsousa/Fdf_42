NAME = fdf

CC = cc

CFLAGS = -Wextra -Wall -Werror

SRCS = main.c parser.c draw.c mlx.c draw_steep.c \
	   isometric.c

SRC_GNL = include/get_next_line_42/get_next_line.c \
			include/get_next_line_42/get_next_line_utils.c \

INC = ./include/libft_42 \
	  ./include/get_next_line_42 \

OBJS = $(SRCS:.c=.o)

OBJS_GNL = $(SRC_GNL:.c=.o)

LIBXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit 

LIBFT = ./include/libft_42/libft.a

%.o: %.c
	@$(CC) $(CFLAGS) -g -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) libft libmlx gnl
	$(CC) -g $(OBJS) $(LIBXFLAGS) $(LIBFT) get_next_line.o get_next_line_utils.o -o $(NAME)

libft:
	@make all -C include/libft_42

libmlx:
	@make -s -C mlx

gnl: $(SRC_GNL)
	$(CC) $(CFLAGS) -c $(SRC_GNL)

re: fclean all

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_GNL)
	@make -C include/libft_42 clean

fclean: clean
	@make -C include/libft_42 fclean
	@rm fdf
	
run: re
	./fdf
