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

int parser(const char *filename, t_map *map)
{
    if (check_filename_sanity(filename))
        return (1);

}
