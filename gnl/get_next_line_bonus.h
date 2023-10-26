/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:06:27 by hbouhach          #+#    #+#             */
/*   Updated: 2022/11/05 14:06:41 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct s_stream
{
	struct s_stream	*previous;
	int				fd;
	char			*stash;
	size_t			stash_size;
	struct s_stream	*next;
}					t_stream;

char				*get_next_line(int fd);
t_stream			*new_stream(int fd);
t_stream			*get_stream(t_stream *streams, int fd);
void				cpynbytes(char *dst, const char *src, size_t count);
void				*patch_streams_list(t_stream **head,
						t_stream *current_stream);
ssize_t				get_char_pos(const char *buffer, char c, size_t length);
#endif
