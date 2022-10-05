NAME = fdf

# compiler
CC = cc
CFLAGS = -Wextra -Wall -Werror -g

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

# source/ objects files
SRC = main.c parser.c draw.c mlx.c draw_steep.c \
	   isometric.c ft_split_int.c
SRC_GNL = include/get_next_line_42/get_next_line.c \
			include/get_next_line_42/get_next_line_utils.c \

OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))
OBJ_GNL = $(SRC_GNL:.c=.o)

# include
INC = ./include/libft_42 \
	  ./include/get_next_line_42 

# mlx library
LIBXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit 

# ft library
LIBFT = ./include/libft_42/libft.a

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@


$(NAME): $(OBJ) libft libmlx gnl
	$(CC) $(OBJ) $(LIBXFLAGS) $(LIBFT) get_next_line.o get_next_line_utils.o -o $(NAME)

libft:
	@make all -C include/libft_42

libmlx:
	@make -s -C mlx

gnl: $(SRC_GNL)
	$(CC) $(CFLAGS) -c $(SRC_GNL)

re: fclean all

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJ_GNL)
	@make -C include/libft_42 clean

fclean: clean
	@make -C include/libft_42 fclean
	@rm fdf
	
run: re
	./fdf
