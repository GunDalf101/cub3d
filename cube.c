/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:46:52 by mbennani          #+#    #+#             */
/*   Updated: 2023/11/03 16:26:29 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

void	 initplayer(t_scene *scene)
{
	int i = 0;
	int j = 0;

	scene->player = malloc(sizeof(t_player));
	while (i < scene->map->map_height)
	{
		j = 0;
		while (j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'N')
			{
				scene->player->pos[Y] = j * UNIT + UNIT / 2;
				scene->player->pos[X] = i * UNIT + UNIT / 2;
			}
			j++;
		}
		i++;
	}
	scene->player->p_angle = 0;
	scene->player->dir[Y] = (double)cosf(scene->player->p_angle) * 25;
	scene->player->dir[X] = (double)sinf(scene->player->p_angle) * 25;
	scene->player->plane[Y] = (double)cosf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->plane[X] = (double)sinf(scene->player->p_angle + M_PI / 2) * 16.5;
	scene->player->health_points = UNIT;
	scene->player->mana_points = UNIT;
	scene->player->central_angle = 0;
	scene->player->is_ded = FALSE;
	scene->player->forward = FALSE;
	scene->player->backwards = FALSE;
	scene->player->left = FALSE;
	scene->player->right = FALSE;
	scene->player->is_running = 1;
	scene->player->is_jumping = FALSE;
	scene->player->is_trapped = FALSE;
	scene->player->is_crouching = FALSE;
	scene->player->will_collide[Y] = FALSE;
	scene->player->will_collide[X] = FALSE;
}

void	dynamic_logic(t_scene *scene)
{
	int height = UNIT;
	int width = UNIT;
	int i = 0;
	if (scene->player->health_points <= 0)
		scene->player->is_ded = TRUE;
	if (scene->map->map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y]) / height] == 'T' && scene->player->health_points > 0)
		scene->player->is_trapped += TRUE;
	else
		scene->player->is_trapped = FALSE;
	if (scene->map->map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y]) / height] == 'M')
	{
		system("afplay assets/restoreMana.mp3 &");
		if (scene->player->mana_points + 10 > UNIT)
			scene->player->mana_points = UNIT;
		else
			scene->player->mana_points += 10;
		while (scene->sprites[i]->sprite_img)
		{
			if ((int)(scene->player->pos[X]) / width == (int)(scene->sprites[i]->pos[X]) / width && (int)(scene->player->pos[Y]) / height == (int)(scene->sprites[i]->pos[Y]) / height)
			{
				scene->sprites[i]->pos[X] = -UNIT;
				scene->sprites[i]->pos[Y] = -UNIT;
				break ;
			}
			i++;
		}
		scene->map->map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y]) / height] = '0';
	}

}

int collision_ray(int x1, int y1, int x2, int y2, t_scene scene) {
	// int height = WIN_HEIGHT / scene.map->map_width;
	// int width = WIN_WIDTH / scene.map->map_height;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

	(void)scene;
    while (1) {
        if (sqrt(pow((x1 - scene.sprites[scene.indexer]->pos[X]), 2) + pow((y1 - scene.sprites[scene.indexer]->pos[Y]), 2)) < scene.sprites[scene.indexer]->collision_box)
			return (TRUE);
        if (x1 == x2 && y1 == y2) {
            break;
        }
        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
	return (FALSE);
}

int	does_it_collide(t_scene *scene, int cas)
{
	int i = 0;

	while (i < scene->sprite_count)
	{
		scene->indexer = i;
		if (cas == 1 && collision_ray(scene->player->pos[X], scene->player->pos[Y], scene->player->pos[X],  scene->player->pos[Y] + scene->player->dir[Y] * scene->move_speed, *scene))
			return (TRUE);
		if (cas == 2 && collision_ray(scene->player->pos[X], scene->player->pos[Y], scene->player->pos[X] + scene->player->dir[X] * scene->move_speed, scene->player->pos[Y], *scene))
			return (TRUE);
		if (cas == 3 && collision_ray(scene->player->pos[X], scene->player->pos[Y], scene->player->pos[X], scene->player->pos[Y] - scene->player->dir[Y] * scene->move_speed, *scene))
			return (TRUE);
		if (cas == 4 && collision_ray(scene->player->pos[X], scene->player->pos[Y], scene->player->pos[X] - scene->player->dir[X] * scene->move_speed, scene->player->pos[Y], *scene))
			return (TRUE);
		if (cas == 5 && collision_ray(scene->player->pos[X], scene->player->pos[Y], scene->player->pos[X], scene->player->pos[Y] - scene->player->plane[Y] * scene->move_speed, *scene))
			return (TRUE);
		if (cas == 6 && collision_ray(scene->player->pos[X], scene->player->pos[Y], scene->player->pos[X] - scene->player->plane[X] * scene->move_speed, scene->player->pos[Y], *scene))
			return (TRUE);
		if (cas == 7 && collision_ray(scene->player->pos[X], scene->player->pos[Y], scene->player->pos[X], scene->player->pos[Y] + scene->player->plane[Y] * scene->move_speed, *scene))
			return (TRUE);
		if (cas == 8 && collision_ray(scene->player->pos[X], scene->player->pos[Y], scene->player->pos[X] + scene->player->plane[X] * scene->move_speed, scene->player->pos[Y], *scene))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	delete_projectile(t_scene *scene, t_projectile *projectile)
{
	t_projectile *tmp = scene->projectiles;
	if (tmp == projectile)
	{
		scene->projectiles = tmp->next;
		tmp = NULL;
		free(tmp);
		return ;
	}
	while (tmp->next != projectile)
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	free(projectile);
}

t_projectile* merge(t_projectile* left, t_projectile* right) {
    t_projectile dummy;
    t_projectile* tail = &dummy;

    while (left && right) {
        if (left->proj_distance > right->proj_distance) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = left ? left : right;

    return dummy.next;
}

t_projectile* proj_sort(t_projectile* head) {
    if (head == NULL || head->next == NULL)
        return head;


    t_projectile* slow = head;
    t_projectile* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    t_projectile* right = slow->next;
    slow->next = NULL;

    t_projectile* leftSorted = proj_sort(head);
    t_projectile* rightSorted = proj_sort(right);

    return merge(leftSorted, rightSorted);
}

void	gameloop(void *scene2)
{
	t_scene	*scene;
	scene = (t_scene *)scene2;
	mlx_delete_image(scene->mlx_ptr, scene->mlx_img);
	scene->mlx_img = mlx_new_image(scene->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	scene->oldtime = scene->time;
	scene->time = mlx_get_time();
	scene->frame_time = (scene->time - scene->oldtime);
	printf("FPS: %f\n", 1 / scene->frame_time);
	int height = UNIT;
	int width = UNIT;
	if (scene->player->forward)
	{
		double delta_x = scene->player->dir[Y] * scene->move_speed;
		double delta_y = scene->player->dir[X] * scene->move_speed;
		if (scene->map->map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + delta_x) / (UNIT)] != '1' && !does_it_collide(scene, 1))
			scene->player->pos[Y] += delta_x;
		if (scene->map->map[(int)(scene->player->pos[X] + delta_y) / (UNIT)][(int)(scene->player->pos[Y]) / height] != '1' && !does_it_collide(scene, 2))
			scene->player->pos[X] += delta_y;
	}
	if (scene->player->backwards)
	{
		if (scene->map->map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->dir[Y] * scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 3))
			scene->player->pos[Y] -= scene->player->dir[Y] * scene->move_speed;
		if (scene->map->map[(int)(scene->player->pos[X] - scene->player->dir[X] * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y]) / height] != '1' && !does_it_collide(scene, 4))
			scene->player->pos[X] -= scene->player->dir[X] * scene->move_speed;
	}
	if (scene->player->left)
	{
		if (scene->map->map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] - scene->player->plane[Y] * scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 5))
			scene->player->pos[Y] -= scene->player->plane[Y] * scene->move_speed;
		if (scene->map->map[(int)(scene->player->pos[X] - scene->player->plane[X] * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y]) / height] != '1' && !does_it_collide(scene, 6))
			scene->player->pos[X] -= scene->player->plane[X] * scene->move_speed;
	}
	if (scene->player->right)
	{
		if (scene->map->map[(int)(scene->player->pos[X]) / width][(int)(scene->player->pos[Y] + scene->player->plane[Y] * scene->move_speed) / (UNIT)] != '1' && !does_it_collide(scene, 7))
			scene->player->pos[Y] += scene->player->plane[Y] * scene->move_speed;
		if (scene->map->map[(int)(scene->player->pos[X] + scene->player->plane[X] * scene->move_speed) / (UNIT)][(int)(scene->player->pos[Y]) / height] != '1' && !does_it_collide(scene, 8))
			scene->player->pos[X] += scene->player->plane[X] * scene->move_speed;
	}
	if (scene->player->is_trapped)
	{
		scene->damaged_time = mlx_get_time();
		if (scene->player->is_trapped == 1.00)
		{
			scene->old_damaged_time = scene->damaged_time;
			if (scene->player->health_points - 10 < 0)
				scene->player->health_points = 0;
			else
				scene->player->health_points -= 10;
		}
		if (scene->damaged_time - scene->old_damaged_time > 1)
		{
			if (scene->player->health_points - 10 < 0)
				scene->player->health_points = 0;
			else
				scene->player->health_points -= 10;
			scene->old_damaged_time = scene->damaged_time;
		}
	}
	t_projectile *tmp = scene->projectiles;
	while (tmp)
	{
		if (tmp && (scene->map->map[(int)(tmp->pos[X]) / width][(int)(tmp->pos[Y]) / height] == '1' || scene->map->map[(int)(tmp->pos[X]) / width][(int)(tmp->pos[Y]) / height] == 'P'))
			delete_projectile(scene, tmp);
		tmp->pos[X] += tmp->dir[X] * tmp->speed;
		tmp->pos[Y] += tmp->dir[Y] * tmp->speed;
		tmp->proj_distance = sqrt(pow((tmp->pos[X] - scene->player->pos[X]), 2) + pow((tmp->pos[Y] - scene->player->pos[Y]), 2));
		tmp = tmp->next;
	}
	scene->projectiles = proj_sort(scene->projectiles);
	if (1 / scene->frame_time < 40)
		scene->frame_time = 1 / 40.0;
	dynamic_logic(scene);
	renderitall(*scene);
	scene->move_speed = scene->frame_time * 5 * scene->player->is_running;
}

void	set_sprites_up(t_scene *scene, int i, int j, int count)
{
	scene->sprites[count]->pos[Y] = j * UNIT + UNIT / 2;
	scene->sprites[count]->pos[X] = i * UNIT + UNIT / 2;
}

void	initsprites(t_scene *scene)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	scene->barrel_tex = mlx_load_png("assets/barrel_01.png");
	scene->barrel_img = mlx_texture_to_image(scene->mlx_ptr, scene->barrel_tex);
	mlx_resize_image(scene->barrel_img, 415, 250);
	mlx_delete_texture(scene->barrel_tex);
	scene->fireball_tex = mlx_load_png("assets/FireBall.png");
	scene->fireball_img = mlx_texture_to_image(scene->mlx_ptr, scene->fireball_tex);
	mlx_resize_image(scene->fireball_img, 200, 200);
	mlx_delete_texture(scene->fireball_tex);
	scene->iceball_tex = mlx_load_png("assets/IceBall.png");
	scene->iceball_img = mlx_texture_to_image(scene->mlx_ptr, scene->iceball_tex);
	mlx_resize_image(scene->iceball_img, 150, 150);
	mlx_delete_texture(scene->iceball_tex);
	scene->pillar_tex = mlx_load_png("assets/Pillar.png");
	scene->pillar_img = mlx_texture_to_image(scene->mlx_ptr, scene->pillar_tex);
	mlx_resize_image(scene->pillar_img, 500, 500);
	mlx_delete_texture(scene->pillar_tex);
	scene->manaorb_tex = mlx_load_png("assets/ManaOrb.png");
	scene->manaorb_img = mlx_texture_to_image(scene->mlx_ptr, scene->manaorb_tex);
	mlx_resize_image(scene->manaorb_img, 251, 282);
	mlx_delete_texture(scene->manaorb_tex);
	while (i < scene->map->map_height)
	{
		j = 0;
		while (j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'B')
				count++;
			if (scene->map->map[i][j] == 'P')
				count++;
			if (scene->map->map[i][j] == 'M')
				count++;
			j++;
		}
		i++;
	}
	scene->sprite_count = count;
	scene->sprites = ft_calloc(count, sizeof(t_sprite *));
	i = 0;
	count = 0;
	while (i < scene->map->map_height)
	{
		j = 0;
		while (j < scene->map->map_width)
		{
			if (scene->map->map[i][j] == 'B')
			{
				scene->sprites[count] = ft_calloc(1, sizeof(t_sprite));
				scene->sprites[count]->sprite_img = scene->barrel_img ;
				scene->sprites[count]->v_move = 1100;
				scene->sprites[count]->collision_box = 40;
				set_sprites_up(scene, i, j, count);
				count++;
			}
			if (scene->map->map[i][j] == 'P')
			{
				scene->sprites[count] = ft_calloc(1, sizeof(t_sprite));
				scene->sprites[count]->sprite_img = scene->pillar_img;
				scene->sprites[count]->v_move = 50;
				scene->sprites[count]->collision_box = 40;
				set_sprites_up(scene, i, j, count);
				count++;
			}
			if (scene->map->map[i][j] == 'M')
			{
				scene->sprites[count] = ft_calloc(1, sizeof(t_sprite));
				scene->sprites[count]->sprite_img = scene->manaorb_img;
				scene->sprites[count]->v_move = -500;
				scene->sprites[count]->collision_box = 0;
				set_sprites_up(scene, i, j, count);
				count++;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_scene		scene;
	scene.map = ft_calloc(sizeof(t_map), 1);
	if (argc != 2)
		return (1);
	if (parser(argv[1], scene.map))
	{
		printf("ERROR\n");
		return (1);
	}

	printf("ceiling: %d,%d,%d\n", scene.map->ceiling_rgb[0], scene.map->ceiling_rgb[1], scene.map->ceiling_rgb[2]);
	printf("floor: %d,%d,%d\n", scene.map->floor_rgb[0], scene.map->floor_rgb[1], scene.map->floor_rgb[2]);

	for (int i = 0; scene.map->map[i]; i++)
	{
		printf(">> [%s] <<\n", scene.map->map[i]);
	}

	printf("map props: %d,%d\n", scene.map->map_width, scene.map->map_height);
	scene.projectiles = NULL;
	initplayer(&scene);
	scene.mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Escape From GunDalf", 1);
	
	
	if (load_textures(scene.mlx_ptr, scene.map))
		return (1);

	exit(0);
	initsprites(&scene);
	scene.time = 0;
	scene.mlx_img = mlx_new_image(scene.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_loop_hook(scene.mlx_ptr, gameloop, &scene);
	mlx_set_cursor_mode(scene.mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(scene.mlx_ptr, hookercur, &scene);
	mlx_key_hook(scene.mlx_ptr, hooker, &scene);
	mlx_loop(scene.mlx_ptr);
	return (0);
}
