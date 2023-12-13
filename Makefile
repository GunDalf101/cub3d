NAME = cub3D

SOURCES = mandatory/cube.c \
		mandatory/free_funcs.c \
		mandatory/rendering/renderer.c \
		mandatory/rendering/rendering_utils.c \
		mandatory/textures.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		mandatory/raycasting/ray_wizard.c \
		mandatory/raycasting/raycast_setup.c \
		mandatory/initialize_game/player_alloc.c \
		mandatory/game_logic/movements.c \
		mandatory/game_logic/main_loop.c \
		mandatory/keybinds/keybinds.c \
		mandatory/parser.c \
		mandatory/parser_.c \
		mandatory/parser__.c \
		mandatory/parser___.c \
		mandatory/parser____.c \
		mandatory/parser_____.c \
		mandatory/parser______.c \

SOURCES_BNS = bonus/cube.c \
		bonus/free_funcs.c \
		bonus/rendering/renderer.c \
		bonus/rendering/render_sprite.c \
		bonus/rendering/render_projectile.c \
		bonus/rendering/render_minimap.c \
		bonus/rendering/rendering_utils.c \
		bonus/rendering/general_object_rendering.c \
		bonus/rendering/sprite_calcul.c \
		bonus/rendering/render_animation.c \
		bonus/rendering/animation_calcul.c \
		bonus/rendering/timer_display.c \
		bonus/rendering/timer_loading.c \
		bonus/rendering/draw_scenes.c \
		bonus/textures.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		bonus/raycasting/ray_wizard.c \
		bonus/raycasting/floor_cast.c \
		bonus/raycasting/raycast_setup.c \
		bonus/raycasting/ceil_cast.c \
		bonus/raycasting/test_color.c \
		bonus/initialize_game/sprite_alloc.c \
		bonus/initialize_game/player_alloc.c \
		bonus/initialize_game/sprite_loader.c \
		bonus/initialize_game/doors_alloc.c \
		bonus/initialize_game/alloc_handler.c \
		bonus/game_logic/collisions.c \
		bonus/game_logic/projectile_logic.c \
		bonus/game_logic/raw_logic.c \
		bonus/game_logic/projectile_sort.c \
		bonus/game_logic/collision_raycast.c \
		bonus/game_logic/movements.c \
		bonus/game_logic/main_loop.c \
		bonus/game_logic/projectile_sprite_interaction.c \
		bonus/game_logic/check_teleport.c \
		bonus/game_logic/logical_numbers.c \
		bonus/game_logic/state_machine.c \
		bonus/game_logic/enemy_los.c \
		bonus/game_logic/check_state.c \
		bonus/keybinds/keybinds.c \
		bonus/keybinds/mousebinds.c \
		bonus/keybinds/door_checker.c \
		bonus/parser.c \
		bonus/parser_.c \
		bonus/parser__.c \
		bonus/parser___.c \
		bonus/parser____.c \
		bonus/parser_____.c \
		bonus/parser______.c \

OBJECTS = $(SOURCES:.c=.o)

OBJECTS_BNS = $(SOURCES_BNS:.c=.o)

INCLUDES = cube.h gnl/get_next_line.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast -funroll-loops
LIBFT = libft/libft.a
all: elderscroll libft gnl $(NAME)
	@if [ $$? -eq 0 ]; then \
		echo "\033[3m\033[1m\033[42m\033[31m~~Nothing to be done for 'all' anymore~~\033[0m"; \
	fi

$(NAME):$(OBJECTS) $(GNLOBJ)
	@cc $(CFLAGS) $(OBJECTS) $(LIBFT) libmlx42.a -L$(shell brew --prefix glfw)/lib -lglfw  -o $(NAME)
	@echo "\033[47m\033[30m\033[1m           \`$@ linked\`           \033[0m"

bonus: elderscroll libft gnl $(OBJECTS_BNS)
	@cc $(CFLAGS) $(OBJECTS_BNS) $(LIBFT) libmlx42.a -L$(shell brew --prefix glfw)/lib -lglfw  -o $(NAME)
	@echo "\033[47m\033[30m\033[1m           \`$@ linked\`           \033[0m"

%.o: %.c bonus/cub3d.h mandatory/cub3d.h gnl/get_next_line.h
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
	@rm -f $(OBJECTS) $(OBJECTS_BNS)
	@make -s -C libft clean
	@echo "\033[3m\033[1m\033[42m\033[31m~~   The objects have been cleaned   ~~\033[0m"; \

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME)
	@echo "\033[3m\033[1m\033[42m\033[31m~~The directory have been fully wiped~~\033[0m"; \

m : all clean
	./cub3d maps/map.cub

re: fclean all

.PHONY: all bonus libft clean fclean re
