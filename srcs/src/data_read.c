/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:07 by ppitzini          #+#    #+#             */
/*   Updated: 2024/07/07 15:02:06 by ppitzini         ###   ########.fr       */
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

// stocker la map et regarder autour de tout les 0 si il y a des 1 ou 0 autour
// si 0 au tout debut d'une ligne, erreur car mur impossible a gauche.

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
		printf(B_G"\n\n-----------------| Data are corrects\xE2\x9C\x93 |\n"
			"-------------\n"RESET);
		read_map(c);
	}
	return (1);
}
