/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:47:01 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/23 23:54:22 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H


# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

# include <stdio.h>
# include <math.h>
#include "/Users/mbennani/.brew/opt/glfw/include/GLFW/glfw3.h"
#include "/Users/mbennani/.brew/opt/glfw/include/GLFW/glfw3native.h"
#include "/Users/mbennani/Documents/MLX42/include/MLX42/MLX42.h"

enum	e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum	e_general
{
	EW,
	NS
};


enum	e_coord
{
	X,
	Y
};

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_door
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
	int 		step[2];
	double		wall_dist;
	int			will_hit;
	int			side;
	int			wall_height;
	double		ray_angle;
}				t_ray;

typedef struct s_player
{
	double		pos[2];
	double		dir[2];
	double		plane[2];
	double		p_angle;
	double		fov;
	t_ray		**collision_rays;
	t_ray		**vision_rays;
}				t_player;

typedef	struct	s_map
{
	char		**map;
	int			map_width;
	int			map_height;
}				t_map;

typedef	struct	s_scene
{
	void		*mlx_ptr;
	void		*mlx_win;
	mlx_image_t	*mlx_img;
	double		camera_x;
	int			fd;
	int			maplol[10][10];
	t_map		*map;
	t_player	*player;
	t_wall		**walls;
	int			win_width;
	int			win_height;
}				t_scene;

#endif