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
        mlx_resize_image(map->textures_mlx_imgs[i], WIN_WIDTH, WIN_HEIGHT);
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

void    drawline_from_textures(t_scene *scene, int x, int start_y, int end_y, int truestart, int trueend)
{
    t_direction wdir;
    int i;
    // printf("draw a line from: (%d,%d) to (%d,%d)\n", x, start_y, x, end_y);
    // get_wall_dir(scene->map, x, start_y);
    // printf("looking at wall: [%s]\n", scene->player->vision_rays[x]->side == EW ? (scene->player->dir[X] < 0 ? "WE" : "EA") : (scene->player->dir[Y] < 0 ? "NO" : "SO"));
    wdir = get_wall_dir(scene->player, x);
    // if (wdir != NORTH && wdir != SOUTH)
    // printf("current wall: (%d, %d) DIR: (%s)\n", scene->player->vision_rays[x]->current_cell[X] / UNIT, scene->player->vision_rays[x]->current_cell[Y] / UNIT, stringity_dir(wdir));
    mlx_image_t *wtext = scene->map->textures_mlx_imgs[wdir];
    if (wdir == EAST || wdir == WEST)
        i = scene->player->vision_rays[x]->current_cell[X] % UNIT;
    else
        i = scene->player->vision_rays[x]->current_cell[Y] % UNIT;
    i = wtext->width / UNIT * i;
    (void)truestart;
    double wh = trueend - truestart;
    wh = wtext->height / wh;
    double y = abs(truestart - start_y) * wh;
    while (start_y < end_y)
    {
        mlx_put_pixel(scene->mlx_img, x, start_y, ft_pixel(wtext->pixels[(int)y * wtext->width * 4 + i * 4], wtext->pixels[(int)y * wtext->width * 4 + i * 4 + 1], wtext->pixels[(int)y * wtext->width * 4 + i * 4 + 2],wtext->pixels[(int)y * wtext->width * 4 + i * 4 + 3]));
        start_y++;
        y += wh;
    }
}
