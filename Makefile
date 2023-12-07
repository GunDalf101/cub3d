NAME = cub3d

SOURCES = cube.c \
		free_funcs.c \
		rendering/renderer.c \
		rendering/render_sprite.c \
		rendering/render_projectile.c \
		rendering/render_minimap.c \
		rendering/rendering_utils.c \
		rendering/general_object_rendering.c \
		rendering/sprite_calcul.c \
		parser.c \
		textures.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		raycasting/ray_wizard.c \
		raycasting/floor_cast.c \
		raycasting/raycast_setup.c \
		raycasting/ceil_cast.c \
		initialize_game/sprite_alloc.c \
		initialize_game/player_alloc.c \
		initialize_game/sprite_loader.c \
		game_logic/collisions.c \
		game_logic/projectile_logic.c \
		game_logic/raw_logic.c \
		game_logic/projectile_sort.c \
		game_logic/collision_raycast.c \
		game_logic/movements.c \
		game_logic/main_loop.c \
		keybinds/keybinds.c \
		keybinds/mousebinds.c \

OBJECTS = $(SOURCES:.c=.o)

INCLUDES = cube.h gnl/get_next_line.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast -g
LIBFT = libft/libft.a
all: elderscroll libft gnl $(NAME)
	@if [ $$? -eq 0 ]; then \
		echo "\033[3m\033[1m\033[42m\033[31m~~Nothing to be done for 'all' anymore~~\033[0m"; \
	fi

$(NAME):$(OBJECTS) $(GNLOBJ)
	@cc $(CFLAGS) $(OBJECTS) $(LIBFT) libmlx42.a -L$(shell brew --prefix glfw)/lib -lglfw  -o $(NAME)
	@echo "\033[47m\033[30m\033[1m           \`$@ linked\`           \033[0m"

%.o: %.c cub3d.h gnl/get_next_line.h
	@$(CC) $(CFLAGS) libmlx42.a -Iinclude -I$(shell brew --prefix glfw)/include -c $< -o $@
	@echo "\033[33m$< compiled \033[0m"


elderscroll:
	@echo '                                             _______________________'
	@echo '   _______________________-------------------                        \'
	@echo ' /:--__                                                              |'
	@echo '||< > |                                   ___________________________/'
	@echo '| \__/_________________-------------------                         |'
	@echo '|                                                                  |'
	@echo ' |                  THE SCROLL OF INFINITE WISDOM                   |'
	@echo ' |                                                                  |'
	@echo ' |       Three Rings for the Elven-kings under the sky,             |'
	@echo '  |        Seven for the Dwarf-lords in their halls of stone,        |'
	@echo '  |      Nine for Mortal Men doomed to die,                          |'
	@echo '  |        One for the Dark Lord on his dark throne                  |'
	@echo '  |      In the Land of Mordor where the Shadows lie.                 |'
	@echo '   |       One Ring to rule them all, One Ring to find them,          |'
	@echo '   |       One Ring to bring them all and in the darkness bind them   |'
	@echo '   |     In the Land of Mordor where the Shadows lie.                |'
	@echo '  |                                                                  |'
	@echo '  |                                    -----------------------       |'
	@echo '  |                                  )) twoheavens && GunDalf ((     |'
	@echo '  |                                    -----------------------       |'
	@echo '  |                                              ____________________|_'
	@echo '  |  ___________________-------------------------                       \'
	@echo '  |/ --_                                                                 |'
	@echo '  ||[ ]||                                            ___________________/'
	@echo '   \===/___________________--------------------------'
	@echo ''

libft:
	@make -s -C libft bonus
	@echo "\033[35m$@ have been made \033[0m"

clean:
	@rm -f $(OBJECTS)
	@make -s -C libft clean
	@echo "\033[3m\033[1m\033[42m\033[31m~~   The objects have been cleaned   ~~\033[0m"; \

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME)
	@echo "\033[3m\033[1m\033[42m\033[31m~~The directory have been fully wiped~~\033[0m"; \

re: fclean all

.PHONY: all bonus libft clean fclean re
