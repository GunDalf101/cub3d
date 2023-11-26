#include "cube.h"

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
        map->textures_mlx_imgs[i] = mlx_texture_to_image(mlxptr, texture);
        mlx_resize_image(map->textures_mlx_imgs[i], WIN_WIDTH, WIN_HEIGHT);
        mlx_delete_texture(texture);
        i++;
    }
    return (0);
}
