
MAKEFLAGS	= --silent
NAME = fdf

# compiler
CC = cc
CFLAGS = -Wextra -Wall -Werror -g

# directories
SRCDIR	=	 ./src/
INCDIR	=	 ./include/
OBJDIR	=	 ./obj/

# source / objects files
SRC =		main.c \
	  		parser.c \
	 	 	draw.c \
			mlx.c\
			draw_steep.c \
	 	 	isometric.c \
	  		ft_split_int.c \
			ft_count_words_str.c \
			get_next_line.c \
			get_next_line_utils.c quit.c

OBJ += $(addprefix $(OBJDIR), $(SRC:.c=.o))

############## mlx library ##############
MLX		= ./miniLibX/
MLX_LIB	= $(addprefix $(MLX), mlx.a)
MLX_INC	= -I ./miniLibX
MLX_LNK	= -L ./miniLibX -l mlx -framework OpenGL -framework AppKit

############### ft library ###############
FT		= ./libft/
FT_LIB	= $(FT)/libft.a
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

############### ft_printf ###############
FT_PTF	=	./ft_printf/
FT_PTF_LIB	=	$(addprefix $(FT_PTF), libftprintf.a)
FT_PTF_INC	=	-I $(FT_PTF)

all: obj $(FT_LIB) $(FT_PTF_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I ft_printf/*.o -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(FT_PTF_LIB):
	make -C $(FT_PTF)

$(MLX_LIB):
	make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) $(FT_PTF_INC) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean
	make -C $(FT_PTF) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

	make -C $(FT_PTF) fclean

re: fclean all

.PHONY: re, fclean, clean
