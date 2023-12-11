#include "cube.h"

static void perror_faulty_texuture(char *fpath)
{
    printf("could not load texture: [%s]\n", fpath);
    exit(1);
}

int load_textures(void *mlxptr, t_map *map)
{
    int i;
    mlx_texture_t   *texture;

    map->textures_mlx_imgs = malloc(sizeof(mlx_image_t *) * 4);
    if (!map->textures_mlx_imgs)
        return (1);
    i = 0;
    while (i < 4)
    {
        texture = mlx_load_png(map->textures_paths[i]);
        if (!texture)
            perror_faulty_texuture(map->textures_paths[i]);
        map->textures_mlx_imgs[i] = mlx_texture_to_image(mlxptr, texture);
        if (!map->textures_mlx_imgs[i])
            perror_faulty_texuture(map->textures_paths[i]);
        mlx_resize_image(map->textures_mlx_imgs[i], WIN_WIDTH, WIN_WIDTH);
        mlx_delete_texture(texture);
        i++;
    }
    return (0);
}

static t_direction  get_wall_dir(t_player *player, int x)
{
    if (player->vision_rays[x]->side == EW)
    {
        if (player->vision_rays[x]->dir[Y] < 0)
            return (WEST);
        else
            return (EAST);
    }
    else if (player->vision_rays[x]->dir[X] < 0)
        return (NORTH);
    return (SOUTH);
}

// static char * stringity_dir(t_direction dir)
// {
//     if (dir == SOUTH)
//         return "SOUTH";
//     else if (dir == EAST)
//         return "EAST";
//     else if (dir == WEST)
//         return "WEST";
//     else
//         return "NORTH";
// }
// if (wdir != NORTH && wdir != SOUTH)
    // printf("current wall: (%d, %d) DIR: (%s)\n", scene->player->vision_rays[x]->current_cell[X] / UNIT, scene->player->vision_rays[x]->current_cell[Y] / UNIT, stringity_dir(wdir));
// printf("draw a line from: (%d,%d) to (%d,%d)\n", x, start_y, x, end_y);
    // get_wall_dir(scene->map, x, start_y);
    // printf("looking at wall: [%s]\n", scene->player->vision_rays[x]->side == EW ? (scene->player->dir[X] < 0 ? "WE" : "EA") : (scene->player->dir[Y] < 0 ? "NO" : "SO"));

void    drawline_from_textures(t_scene *scene, t_ray_caster *wizard)
{
    t_direction	wdir;
    int			i;
	mlx_image_t *wtext;
	double		wh;
	double		y;

    wdir = get_wall_dir(scene->player, wizard->x);
    if (scene->map->map[scene->player->\
			vision_rays[wizard->x]->current_cell[X] \
			/ UNIT][scene->player->vision_rays[wizard->x]->current_cell[Y]
			/ UNIT] == 'D')
        wtext = scene->door_img;
    else if (scene->map->map[scene->player->\
            vision_rays[wizard->x]->current_cell[X] \
            / UNIT][scene->player->vision_rays[wizard->x]->current_cell[Y]
            / UNIT] == 'L')
        wtext = scene->end_img;
    else
        wtext = scene->map->textures_mlx_imgs[wdir];
    if (wdir == EAST || wdir == WEST)
        i = scene->player->vision_rays[wizard->x]->current_cell[X] % UNIT;
    else
        i = scene->player->vision_rays[wizard->x]->current_cell[Y] % UNIT;
    i = wtext->width / UNIT * i;
    wh = wizard->trueend - wizard->truestart;
    wh = wtext->height / wh;
    y = abs(wizard->truestart - wizard->linestart) * wh;
    while (wizard->linestart < wizard->lineend)
    {
        mlx_put_pixel(scene->mlx_img, wizard->x, wizard->linestart, ft_pixel(wtext->pixels[(int)y * wtext->width * 4 + i * 4], wtext->pixels[(int)y * wtext->width * 4 + i * 4 + 1], wtext->pixels[(int)y * wtext->width * 4 + i * 4 + 2],wtext->pixels[(int)y * wtext->width * 4 + i * 4 + 3]));
        wizard->linestart++;
        y += wh;
    }
}
