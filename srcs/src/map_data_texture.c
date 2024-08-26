/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:27:35 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/26 16:26:49 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	put_path_extend(t_core *c, int what, char *line)
{
	if (what == 3)
	{
		c->texture->we = ft_strdup_end(line);
		file_exists(c->texture->we, c);
		if (extension(c->texture->we, ".png"))
			error_extension(c);
		c->map->WE = 1;
	}
	if (what == 4)
	{
		c->texture->ea = ft_strdup_end(line);
		file_exists(c->texture->ea, c);
		if (extension(c->texture->we, ".png"))
			error_extension(c);
		c->map->EA = 1;
	}
}

void	put_path(t_core *c, int what, char *line)
{
	if (what == 1)
	{
		c->texture->no = ft_strdup_end(line);
		file_exists(c->texture->no, c);
		if (extension(c->texture->no, ".png"))
			error_extension(c);
		c->map->NO = 1;
	}
	if (what == 2)
	{
		c->texture->so = ft_strdup_end(line);
		file_exists(c->texture->so, c);
		if (extension(c->texture->so, ".png"))
			error_extension(c);
		c->map->SO = 1;
	}
	if (what == 3 || what == 4)
		put_path_extend(c, what, line);
}

int	test_it(char *line, t_core *c, int what)
{
	line += 2;
	while (*line == ' ')
		line++;
	if (*line == '\n')
	{
		error_open_file(c);
	}
	put_path(c, what, line);
	return (1);
}

int	is_valid_data(char *line, t_core *c)
{
	while (*line == ' ')
		line++;
	if ((*line == 'N' && *(line + 1) == 'O')
		|| (*line == 'N' && *(line + 1) == ' '))
	{
		if (c->map->NO)
			textures_error_alloc(c);
		else
			return (test_it(line, c, 1));
	}
	else if ((*line == 'S' && *(line + 1) == 'O')
		|| (*line == 'S' && *(line + 1) == ' '))
	{
		if (c->map->SO)
			textures_error_alloc(c);
		else
			return (test_it(line, c, 2));
	}
	else
		return (is_valid_data_extend(line, c));
	return (1);
}

void	take_map_data(t_core *c)
{
	printf(B_Y"\n----| Checking Data\n\n"RESET);
	while (!c->data_ok && c->line)
	{
		while (c->line && c->line[0] == '\n')
		{
			free(c->line);
			c->line = get_next_line(c->map->fd);
		}
		if (!is_valid_data(c->line, c))
			error_data(c);
		free(c->line);
		c->line = get_next_line(c->map->fd);
		if (!c->line)
			error_map(c);
		if (c->map->NO && c->map->SO && c->map->WE &&
			c->map->EA && c->map->C && c->map->F)
			c->data_ok = 1;
	}
	free(c->line);
	if (!c->data_ok)
		error_data(c);
}
