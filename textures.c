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

void    drawline_from_textures(t_scene *scene, int x, int start_y, int end_y)
{
    (void)scene;
    printf("draw a line from: [%d,%d] to [%d,%d]\n", x, start_y, x, end_y);
}
