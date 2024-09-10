/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:07 by ppitzini          #+#    #+#             */
/*   Updated: 2024/09/10 13:01:26 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	skip_lines(int fd, t_core *c)
{
	c->line = get_next_line(fd);
	while (c->line && c->line[0] == '\n')
	{
		free(c->line);
		c->line = get_next_line(fd);
		if (!c->line)
			error_map(c);
	}
}

int	read_hub(t_core *c)
{
	c->map->fd = open(c->map->map_path, O_RDONLY);
	if (c->map->fd == -1)
	{
		error_open_file(c);
	}
	skip_lines(c->map->fd, c);
	take_map_data(c);
	if (c->data_ok)
	{
		printf(B_G"\n\n-----------------| Data are corrects\xE2\x9C\x93 |"
			"-------------\n"RESET);
		read_map(c);
	}
	return (1);
}

int	is_good_data(char cell)
{
	if (cell == '0' || cell == '1' || cell == 'N'
		|| cell == 'S' || cell == 'E' || cell == 'W')
		return (1);
	else
		return (0);
}
