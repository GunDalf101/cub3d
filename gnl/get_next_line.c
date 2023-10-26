/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:27:38 by hbouhach          #+#    #+#             */
/*   Updated: 2022/11/05 12:53:53 by hbouhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	realloc_and_join(t_stream *current_stream, const char *read_buffer,
		size_t read_buffer_length)
{
	char	*buffer;

	if (!current_stream->stash)
	{
		current_stream->stash = malloc(read_buffer_length);
		if (!current_stream->stash)
			return (-1);
		cpynbytes(current_stream->stash, read_buffer, read_buffer_length);
		current_stream->stash_size = read_buffer_length;
		return (0);
	}
	else
	{
		buffer = malloc(current_stream->stash_size + read_buffer_length);
		if (!buffer)
			return (-1);
		cpynbytes(buffer, current_stream->stash, current_stream->stash_size);
		cpynbytes(buffer + current_stream->stash_size, read_buffer,
			read_buffer_length);
		free(current_stream->stash);
		current_stream->stash = buffer;
		current_stream->stash_size += read_buffer_length;
		return (0);
	}
}

static int	adjust_stash(t_stream *current_stream)
{
	ssize_t	new_line_pos;
	char	*stash;

	new_line_pos = get_char_pos(current_stream->stash, '\n',
			current_stream->stash_size);
	if (new_line_pos < 0)
	{
		current_stream->stash_size = 0;
		return (0);
	}
	stash = malloc(current_stream->stash_size - new_line_pos - 1);
	if (!stash)
		return (-1);
	cpynbytes(stash, current_stream->stash + new_line_pos + 1,
		(current_stream->stash_size - new_line_pos - 1));
	free(current_stream->stash);
	current_stream->stash = stash;
	current_stream->stash_size -= (new_line_pos + 1);
	return (0);
}

static char	*get_line_from_stash(t_stream *current_stream)
{
	ssize_t	new_line_pos;
	char	*line;

	if (!current_stream->stash_size)
		return (NULL);
	new_line_pos = get_char_pos(current_stream->stash, '\n',
			current_stream->stash_size);
	if (new_line_pos < 0)
		new_line_pos = current_stream->stash_size - 1;
	line = malloc(new_line_pos + 1 + 1);
	if (!line)
		return (NULL);
	cpynbytes(line, current_stream->stash, new_line_pos + 1);
	line[new_line_pos + 1] = '\0';
	return (line);
}

static int	read_line(t_stream *current_stream)
{
	char	*buffer;
	ssize_t	buffer_length;
	int		status;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (-1);
	buffer_length = 0;
	status = 0;
	while ((get_char_pos(buffer, '\n', buffer_length) == -1))
	{
		buffer_length = read(current_stream->fd, buffer, BUFFER_SIZE);
		if (buffer_length < 0)
			status = 1;
		if (!buffer_length)
			status = 2;
		if (status)
			break ;
		status = realloc_and_join(current_stream, buffer, buffer_length);
		if (status)
			break ;
	}
	free(buffer);
	return (status);
}

char	*get_next_line(int fd)
{
	static t_stream	*streams;
	t_stream		*current_stream;
	char			*line;
	int				status;

	if (BUFFER_SIZE < 1 || (read(fd, &status, 0) < 0))
		return (patch_streams_list(&streams, get_stream(streams, fd)));
	if (!streams)
		streams = new_stream(fd);
	current_stream = get_stream(streams, fd);
	if (!current_stream)
		return (NULL);
	status = read_line(current_stream);
	if (status == 1 || status == -1)
		return (patch_streams_list(&streams, current_stream));
	line = get_line_from_stash(current_stream);
	if (status == 2 && !current_stream->stash_size)
	{
		patch_streams_list(&streams, current_stream);
		return (line);
	}
	if (adjust_stash(current_stream))
		return (patch_streams_list(&streams, current_stream));
	return (line);
}
