/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:47:01 by mbennani          #+#    #+#             */
/*   Updated: 2023/07/21 03:58:24 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
#include "/Users/mbennani/.brew/opt/glfw/include/GLFW/glfw3.h"
#include "/Users/mbennani/.brew/opt/glfw/include/GLFW/glfw3native.h"
#include "/Users/mbennani/Documents/MLX42/include/MLX42/MLX42.h"



typedef	struct	s_general
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			fd;
	int			win_width;
	int			win_height;
}				t_general;

#endif