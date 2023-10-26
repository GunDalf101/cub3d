#include "cube.h"

static int check_filename_sanity(const char *filename)
{
    int flen = ft_atoi(filename);

    if (flen > 4
        && filename[flen - 4] == '.'
        && filename[flen - 3] == 'c'
        && filename[flen - 2] == 'u'
        && filename[flen - 1] == 'b')
        return (0);
    return (1);
}

static int open_file(char *filename, int *fd)
{
    *fd = open(filename, O_RDONLY);
    return (*fd);
}

static int arr_size(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}

static char *non_empty_gnl(int fd)
{
    char    *l;

    while (1)
    {
        l = get_next_line(fd);
        if (!l)
            break;
        if (l[0] == '\n' && l[1] == '\0')
        {
            free(l);
            continue;
        }
        return (l);
    }
    return (NULL);
}

static int verify_sprite(char **splited, char *dirs[4], int seen[4], int *tfds)
{
    int i;

    if (arr_size(splited) != 2)
        return (1);
    if (ft_strlen(splited[0]) != 2)
        return (1);
    i = 0;
    while (i < 4)
    {
        if (!ft_strncmp(dirs[i], splited[0], 2) && !seen[i])
        {
            seen[i] = 1;
            break;
        }
        i++;
    }
    if (i == 4)
        return (1);
    if (open_file(splited[1], tfds + i) < 0)
        return (1);
    return (0);
}

static int read_textures(t_map *map, int fd, int *tfds)
{
    char    *line[4];
    char    **splited;
    int     i;
    char    *dirs[4] = {"NO", "SO", "WE", "EA"};
    int     seen[4] = {0, 0, 0, 0};

    i = 0;
    while (i < 4)
        line[i++] = non_empty_gnl(fd);
    i = 0;
    while (i < 4)
    {
        if (!line[i])
            return (1);
        splited = ft_split(line[i], ' ');
        if (!splited)
            return (1);
        if (verify_sprite(splited, dirs, seen, tfds))
            return (1);
        i++;
    }
    return (0);
}

static int fill_rgb(int rgb[3], char *rgbl)
{
    char    **splited;
    int     i;
    int     ret;

    splited = ft_split(rgbl, ',');
    if (arr_size(splited) != 3)
        return (1);
    i = 0;
    while (i < 3)
    {
        ret = ft_atoi(splited[i]);
        if (ret < 0 || ret > 255)
            return (1);
        rgb[i++] = ret;
    }
    return (0);
}

static int read_rgbs(t_map *map, int fd)
{
    char    *l;
    char    **splited;
    char    *known = {'F', 'C'};
    int     i;
    char    *ret;

    i = 0;
    while (i < 2)
    {
        l = non_empty_gnl(fd);
        if (!l)
            return (1);
        splited = ft_split(l, ' ');
        if (arr_size(splited) != 2)
            return (1);
        if (!splited[0][1])
        {
            ret = ft_strchr(known, splited[0]);
            if (!ret)
                return (1);
            else if (!(ret - known))
            {
                if (fill_rgb(&map->floor_rgb, splited[1]))
                    return (1);
                known++;
            }
            else
            {
                if (fill_rgb(map->ceiling_rgb, splited[1]))
                    return (1);
                known[1] = '\0';
            }
        }
        else
            return (1);
        i++;
    }
    if (!*known)
        return (0);
    return (1);
}

int parser(const char *filename, t_map *map)
{
    int fd;
    int tfds[4];

    if (check_filename_sanity(filename))
        return (1);
    if (open_file(filename, &fd) < 0)
        return (1);
    if (read_textures(map, fd, tfds))
        return (1);
    if (read_rgbs(map, fd))
        return (1);
}
