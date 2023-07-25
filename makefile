NAME = cub3D
LIBFT = libft/libft.a
CFLAGS = -Wall -Wextra -Werror 

RM = rm -f
SRC = leaks_curr.c leaks_curr_utils.c cub.c put_pixels.c get_next_line.c get_next_line_utils.c check_map.c check_map_utils.c fill_args.c exc.c get_color.c my_put_pixel.c textuer.c move_player.c
OBJ = $(SRC:.c=.o)

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) -Ofast -lmlx -framework OpenGL -framework AppKit  $(SRC) $(LIBFT)  -o $(NAME) 

$(LIBFT):
	make all -C libft

clean:
	$(RM) $(OBJ)
	make clean -C libft 

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft 

re: fclean all 