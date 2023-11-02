/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:58:24 by hbouhach          #+#    #+#             */
/*   Updated: 2022/11/05 12:58:26 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_char_pos(const char *buffer, char c, size_t length)
{
	size_t	pos;

	pos = 0;
	while (pos < length)
	{
		if (buffer[pos] == c)
			return (pos);
		pos++;
	}
	return (-1);
}

void	cpynbytes(char *dst, const char *src, size_t count)
{
	size_t	pos;

	if (!count || !dst || !src)
		return ;
	pos = 0;
	while (pos < count)
	{
		dst[pos] = src[pos];
		pos++;
	}
}

t_stream	*new_stream(int fd)
{
	t_stream	*stream;

	stream = malloc(sizeof(t_stream));
	if (!stream)
		return (NULL);
	stream->previous = NULL;
	stream->fd = fd;
	stream->stash = NULL;
	stream->stash_size = 0;
	stream->next = NULL;
	return (stream);
}

t_stream	*get_stream(t_stream *streams, int fd)
{
	while (streams)
	{
		if (streams->fd == fd)
			return (streams);
		if (!streams->next)
		{
			streams->next = new_stream(fd);
			if (!streams->next)
				return (NULL);
			streams->next->previous = streams;
			return (streams->next);
		}
		streams = streams->next;
	}
	return (NULL);
}

void	*patch_streams_list(t_stream **streams, t_stream *current_stream)
{
	t_stream	*previous;
	t_stream	*next;

	if (*streams && current_stream)
	{
		previous = current_stream->previous;
		next = current_stream->next;
		if (*streams == current_stream)
			*streams = (*streams)->next;
		if (next)
			next->previous = previous;
		if (previous)
			previous->next = next;
		if (current_stream->stash)
			free(current_stream->stash);
		free(current_stream);
	}
	return (NULL);
}
