/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GunDalf <GunDalf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:47:01 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/26 17:44:23 by GunDalf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1100

# include "/usr/local/opt/glfw/include/GLFW/glfw3.h"
# include "/usr/local/opt/glfw/include/GLFW/glfw3native.h"
# include "/Users/GunDalf/Documents/MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
# include <stdio.h>

enum			e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum			e_move
{
	FORWARD,
	BACKWARDS,
	LEFT,
	RIGHT,
	STOP
};


enum			e_general
{
	EW,
	NS
};

enum			e_coord
{
	Y,
	X
};

enum			e_bool
{
	FALSE,
	TRUE
};

enum			e_door
{
	CLOSED,
	OPEN
};

typedef struct s_door
{
	double		a[2];
	double		b[2];
	int			state;
}				t_door;

typedef struct s_wall
{
	double		a[2];
	double		b[2];
}				t_wall;

typedef struct s_ray
{
	double		pos[2];
	double		dir[2];
	int			current_cell[2];
	double		side_cell[2];
	double		delta_ray[2];
	int			step[2];
	double		wall_dist;
	int			will_hit;
	int			side;
	int			wall_height;
	double		ray_angle;
}				t_ray;

typedef struct s_sprite
{
	double				pos[2];
	double				relative_pos[2];
	double				transform[2];
	double				inverse_det;
	double				sprite_distance;
	double				perp_dist;
	int					sprite_screen_x;
	int					sprite_height;
	int					sprite_width;
	int					tex[2];
	int 				d;
	int					v_move;
	int					v_move_screen;
	int					start[2];
	int					end[2];
	mlx_texture_t		*sprite_texture;
	mlx_image_t			*sprite_img;
}				t_sprite;

typedef struct s_player
{
	double		pos[2];
	double		dir[2];
	double		plane[2];
	double		p_angle;
	double		central_angle;
	int			forward;
	int			backwards;
	int			left;
	int			right;
	double		is_running;
	double		is_jumping;
	double		is_trapped;
	double		is_crouching;
	t_ray		**vision_rays;
	int			health_points;
	int			mana_points;
	int			is_ded;
}				t_player;

typedef struct s_map
{
	char		**map;
	int			map_height;
	int			map_width;
}				t_map;

typedef struct s_scene
{
	void		*mlx_ptr;
	void		*mlx_win;
	mlx_image_t	*mlx_img;
	double		camera_x;
	int			fd;
	int			maplol[10][10];
	t_map		*map;
	t_sprite	**sprites;
	t_player	*player;
	t_wall		**walls;
	int			win_width;
	int			win_height;
	double		frame_time;
	double		time;
	double		oldtime;
	double		damaged_time;
	double		old_damaged_time;
	double		*dist2;
	double		*z_buffer;
	double		*dist_buffer;
	double		move_speed;
	double		rot_speed;
	int			sprite_count;
	mlx_texture_t		*texture;
	mlx_texture_t	*barrel_tex;
	mlx_image_t		*barrel_img;
	mlx_texture_t	*pillar_tex;
	mlx_image_t		*pillar_img;
	mlx_key_data_t			key_data;
}				t_scene;

void	ray_caster(t_scene *scene);
void	renderitall(t_scene scene);
void	drawbar(t_scene scene);
void	drawline(int x1, int y1, int x2, int y2, t_scene scene, int color);
void	hookercur(double xpos, double ypos, void* scene2);
void	hooker(mlx_key_data_t keycode, void *scene2);

#endif