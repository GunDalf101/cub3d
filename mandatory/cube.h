/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:47:01 by mbennani          #+#    #+#             */
/*   Updated: 2023/12/14 01:14:47 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# define WIN_WIDTH 1000
# define WIN_HEIGHT 600
# define MINIMAP_SCALE_FACTOR 0.015
# define UNIT 1000

# define EX_MAP_KNOWN_CHARS "1*0*N!S!W!E!"
# define MAP_KNOWN_CHARS "10NSWE"

# include "../MLX42/include/MLX42/MLX42.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}						t_direction;

enum					e_general
{
	EW,
	NS
};

enum					e_state
{
	IDLE,
	PURSUIT,
	ATTACK,
	DEAD
};

enum					e_coord
{
	Y,
	X
};

enum					e_bool
{
	FALSE,
	TRUE
};

enum					e_door
{
	CLOSED,
	OPEN
};

enum					e_projectile
{
	NONE,
	FIREBALL,
	ICEBALL
};

enum					e_sprite
{
	BARREL,
	PILLAR,
	MANAORB,
	WARLOCK,
	PORTAL
};

typedef struct s_door
{
	int					state;
	int					pos[2];
}						t_door;

typedef struct s_ray_caster
{
	int					x;
	int					linestart;
	int					truestart;
	int					lineend;
	int					trueend;
}						t_ray_caster;

typedef struct s_floor_cast
{
	int					y;
	double				ray_dir_x0;
	double				ray_dir_y0;
	double				ray_dir_x1;
	double				ray_dir_y1;
	int					p;
	double				ray_pos_z;
	double				row_distance;
	double				floor_step_x;
	double				floor_step_y;
	double				floor_x;
	double				floor_y;
	int					x;
	double				current_dist;
	double				weight;
	double				current_floor_x;
	double				current_floor_y;
	int					tx;
	int					ty;
	int					color;
	int					cell_x;
	int					cell_y;
}						t_floor_cast;

typedef struct s_ray
{
	double				pos[2];
	double				dir[2];
	int					current_cell[2];
	double				side_cell[2];
	double				delta_ray[2];
	int					step[2];
	double				wall_dist;
	int					will_hit;
	int					side;
	int					wall_height;
	double				ray_angle;
}						t_ray;

typedef struct s_dda
{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					err2;
	int					x1;
	int					y1;
	unsigned int		color;

}						t_dda;

typedef struct s_projectile
{
	double				pos[2];
	double				dir[2];
	double				speed;
	int					proj_type;
	double				relative_pos[2];
	double				transform[2];
	double				inverse_det;
	double				proj_distance;
	double				perp_dist;
	int					proj_screen_x;
	int					proj_height;
	int					proj_width;
	int					tex[2];
	int					d;
	int					v_move;
	int					v_move_screen;
	double				damage;
	int					start[2];
	int					end[2];
	mlx_image_t			*proj_img;
	struct s_projectile	*next;
}						t_projectile;

typedef struct s_sprite
{
	double				pos[2];
	double				relative_pos[2];
	double				dir[2];
	double				transform[2];
	double				inverse_det;
	double				sprite_distance;
	double				perp_dist;
	int					hitpoint;
	int					sprite_type;
	int					state;
	int					hitbox;
	int					sprite_screen_x;
	int					sprite_height;
	int					sprite_width;
	int					tex[2];
	int					sped;
	int					d;
	int					collision_box;
	int					v_move;
	int					v_move_screen;
	int					start[2];
	int					end[2];
	mlx_image_t			*sprite_img;
	mlx_image_t			*animation_img;
}						t_sprite;

typedef struct s_player
{
	double				pos[2];
	double				dir[2];
	double				plane[2];
	double				p_angle;
	double				central_angle;
	int					forward;
	int					backwards;
	int					left;
	int					right;
	int					rot_left;
	int					rot_right;
	int					attacking;
	double				velocity;
	double				is_jumping;
	double				is_trapped;
	double				crouch;
	t_ray				**vision_rays;
	int					health_points;
	int					mana_points;
	int					is_ded;
	int					will_collide[2];
}						t_player;

typedef struct s_minimap
{
	t_dda				dda;
	double				player_pos_x;
	double				player_pos_y;
	double				i;
	double				j;
	double				pos_x;
	double				pos_y;
	double				k;
	double				l;
	double				o_x;
	double				o_y;
}						t_minimap;

typedef struct s_death
{
	u_int32_t			i;
	u_int32_t			j;
	u_int8_t			r;
	u_int8_t			g;
	u_int8_t			b;
	u_int8_t			a;
}						t_death;

typedef struct s_map
{
	unsigned char		floor_rgb[3];
	char				**map;
	int					map_width;
	int					map_height;
	char				**textures_paths;
	mlx_image_t			**textures_mlx_imgs;
	unsigned char		ceiling_rgb[3];
}						t_map;

typedef struct s_timer
{
	int					time_origin;
	int					time_current;
	int					seconds;
	int					minutes;
	int					hours;
	mlx_image_t			*timer_img;
}						t_timer;

typedef struct s_scene
{
	void				*mlx_ptr;
	void				*mlx_win;
	mlx_image_t			*mlx_img;
	t_timer				timer;
	double				camera_x;
	int					fd;
	int					fast_travel;
	int					north_pole[2];
	int					south_pole[2];
	int					maplol[10][10];
	int					score;
	t_map				*map;
	t_sprite			**sprites;
	t_door				**doors;
	int					door_count;
	int					war_index;
	t_player			*player;
	int					win_width;
	int					win_height;
	double				frame_time;
	double				time;
	double				oldtime;
	double				damaged_time;
	double				old_damaged_time;
	double				*dist2;
	double				*z_buffer;
	double				*dist_buffer;
	double				move_speed;
	double				rot_speed;
	int					sprite_count;
	int					indexer;
	int					anim_count;
	int					*anim_ids;
	int					win;
	mlx_texture_t		*texture;
	mlx_texture_t		*barrel_tex;
	mlx_image_t			*barrel_img;
	mlx_texture_t		*pillar_tex;
	mlx_image_t			*pillar_img;
	mlx_texture_t		*fireball_tex;
	mlx_image_t			*fireball_img;
	mlx_texture_t		*manaorb_tex;
	mlx_image_t			*manaorb_img;
	mlx_texture_t		*iceball_tex;
	mlx_image_t			*iceball_img;
	mlx_texture_t		*trap_tex;
	mlx_image_t			*trap_img;
	mlx_texture_t		*end_tex;
	mlx_image_t			*end_img;
	mlx_texture_t		*win_tex;
	mlx_image_t			*win_img;
	mlx_texture_t		*floor_tex;
	mlx_image_t			*floor_img;
	mlx_texture_t		*door_tex;
	mlx_image_t			*door_img;
	mlx_texture_t		*ending_tex;
	mlx_image_t			*ending_img;
	mlx_texture_t		*ceil_tex;
	mlx_image_t			*ceil_img;
	mlx_texture_t		*portal_tex;
	mlx_image_t			*portal_img;
	mlx_key_data_t		key_data;
	mlx_image_t			*score_img;
	t_projectile		*projectiles;
	mlx_image_t			**evil_warlock;
	mlx_image_t			**finn_sword;
}						t_scene;

void					ray_caster(t_scene *scene);
void					initsprites(t_scene *scene);
void					renderitall(t_scene scene);
void					drawbar(t_scene scene);
void					drawline(t_dda *dda, int x2, int y2, t_scene scene);
void					hookercur(double xpos, double ypos, void *scene2);
void					hooker(mlx_key_data_t keycode, void *scene2);
int32_t					ft_pixel(u_int8_t r, u_int8_t g, u_int8_t b,
							u_int8_t a);
void					floor_casting(t_scene *scene);
void					allocat_player(t_scene *scene);
void					projectile_logic(t_scene *scene);
void					dynamic_logic(t_scene *scene);
void					load_sprites(t_scene *scene);
void					load_projectiles(t_scene *scene);
void					sprite_count(t_scene *scene);
int						collision_ray(t_dda dda, int x2, int y2, t_scene scene);
t_projectile			*proj_sort(t_projectile *head);
void					initial_calculation(t_scene *scene, int count);
void					line_coordinates(t_scene *scene, int count);
void					setup_rays(t_scene *scene, t_ray_caster *wizard);
int						final_free(t_scene *scene);
int						occasional_free(t_scene *scene);

int						parser(char *filename, t_map *map);
int						load_textures(void *mlxptr, t_map *map);
void					drawline_from_textures(t_scene *scene,
							t_ray_caster *wizard);
int						does_it_collide(t_scene *scene, int cas);
void					delete_projectile(t_scene *scene,
							t_projectile *projectile);
void					add_projectile(t_scene *scene, int projectile_type);
void					spawn_sprites(t_scene *scene, int count);
void					spawn_proj(t_scene *scene, t_projectile *projectile);
void					sort_sprites(t_sprite **sprites, int count);
void					draw_minimap_circle(t_scene *scene);
void					drawbar(t_scene scene);
void					sky_floor_render(t_scene scene);
void					death_screen(t_scene scene);
void					gameloop(void *scene2);
void					move_forward(t_scene *scene);
void					move_backward(t_scene *scene);
void					move_left(t_scene *scene);
void					move_right(t_scene *scene);
void					load_floor_textures(t_scene *scene);
void					ceiling_casting(t_scene *scene);
void					load_warlock(void *mlxptr, t_scene *scene);
void					animated_sprite(t_scene scene, int i, int frame);
void					allocat_warlock(t_scene *scene, int i, int j,
							int *count);
void					initial_anime_calculation(t_scene *scene, int count);
void					animated_line_coord(t_scene *scene, int count);
int						projectile_collide(t_scene *scene,
							t_projectile *projectile);

int						parser(char *filename, t_map *map);
int						check_filename_sanity(const char *filename);
void					free_array(char **arr);
int						open_file(char *filename, int *fd);
int						arr_size(char **arr);
char					*strip_line(char *l);
int						is_all_digit(char *str);
char					*non_empty_gnl(int fd);
int						arr_has_any(int *arr, int len, int v);
char					**clone_arr(char **arr);
int						arr_push(char ***lv, char *nl);
int						close_temp_fds(int tfds[4]);
int						str_starts_with(char *str, char *s);
int						pad_map(t_map *map);
int						*init_stuff(char **ll, int *i);
int						*gen_arr_info(char **arr);
int						token_count_in_str(char *str, char c);
int						read_map(t_map *map, int fd);
int						read_texture(t_map *map, char *l, int *tfds);
int						set_map_props(t_map *map);
int						check_token_counts(char **map_lines);
int						read_rgbs(t_map *map, char *l);
int						verify_sprite(t_map *map, char **splited, int seen[4],
							int *tfds);
int						fill_rgb(unsigned char rgb[3], char *rgbl);
int						check_token_counts(char **map_lines);
int						ends_with_ws(char *s);
void					allocat_doors(t_scene *scene);
int						start_walled(char *line);
int						end_walled(char *line);
void					check_door(mlx_key_data_t keycode, t_scene *scene);
void					load_end(t_scene *scene);
void					drawtimer(t_scene scene);
void					load_timer(t_scene *scene);
void					win_screen(t_scene scene);
void					check_pole(t_scene *scene);
void					allocat_sprites(t_scene *scene);
void					allocat_barrel(t_scene *scene, int i, int j,
							int *count);
void					allocat_pillar(t_scene *scene, int i, int j,
							int *count);
void					allocat_manaorb(t_scene *scene, int i, int j,
							int *count);
void					allocat_portal(t_scene *scene, int i, int j,
							int *count);
void					check_win(t_scene *scene);
void					check_timer(t_scene *scene);
void					draw_ending(t_scene scene);
void					check_enemy_state(t_scene *scene);
void					state_machine(t_scene *scene);
int						line_o_sight(t_dda dda, int x2, int y2, t_scene scene);
void					load_sword(void *mlxptr, t_scene *scene);
void					draw_attack(t_scene *scene);
void					melee_attack(t_scene *scene);
int						test_color(t_scene *scene, t_floor_cast *floor);

#endif
