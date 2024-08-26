/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extends_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:10:11 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/26 16:34:43 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_surrounding_cells(t_core *c, int i, int j)
{
	if (c->map->map[i][j] == '0' || c->map->map[i][j] == 'N'
		|| c->map->map[i][j] == 'S' || c->map->map[i][j] == 'E'
		|| c->map->map[i][j] == 'W')
	{
		if (i > 0 && !is_good_data(c->map->map[i - 1][j]))
			error_wall(c, i - 1, j);
		if (c->map->map[i + 1] != NULL
			&& !is_good_data(c->map->map[i + 1][j]))
			error_wall(c, i + 1, j);
		if (j > 0 && !is_good_data(c->map->map[i][j - 1]))
			error_wall(c, i, j - 1);
		if (c->map->map[i][j + 1] != '\0'
			&& !is_good_data(c->map->map[i][j + 1]))
			error_wall(c, i, j + 1);
	}
}

int	is_valid_data_extend(char *line, t_core *c)
{
	if ((*line == 'W' && *(line + 1) == 'E')
		|| (*line == 'W' && *(line + 1) == ' '))
	{
		if (c->map->WE)
			textures_error_alloc(c);
		else
			return (test_it(line, c, 3));
	}
	else if ((*line == 'E' && *(line + 1) == 'A')
		|| (*line == 'E' && *(line + 1) == ' '))
	{
		if (c->map->EA)
			textures_error_alloc(c);
		else
			return (test_it(line, c, 4));
	}
	else
		color_process(line, c);
	return (1);
}

int	str_len_modif(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}
