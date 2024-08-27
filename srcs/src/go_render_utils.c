/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:38:45 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/27 17:24:35 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_pos_player_x(t_core *c, int check)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < c->map->height_line)
	{
		while (c->map->map[x][y])
		{
			if (c->map->map[x][y] == 'N' || c->map->map[x][y] == 'S'
				|| c->map->map[x][y] == 'E' || c->map->map[x][y] == 'W')
			{
				if (check == 0)
					return (x * 16 + 8);
				else if (check == 2)
					return (x);
				else
					return (x * 64 + 32);
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

int	get_pos_player_y(t_core *c, int check)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < c->map->height_line)
	{
		while (c->map->map[x][y])
		{
			if (c->map->map[x][y] == 'N' || c->map->map[x][y] == 'S'
				|| c->map->map[x][y] == 'E' || c->map->map[x][y] == 'W')
			{
				if (check == 0)
					return (y * 16 + 8);
				else if (check == 2)
					return (y);
				else
					return (y * 64 + 32);
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

double	get_angle_player(t_core *c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < c->map->height_line)
	{
		while (c->map->map[x][y])
		{
			if (c->map->map[x][y] == 'N')
				return ((3 * M_PI) / 2);
			if (c->map->map[x][y] == 'S')
				return (M_PI / 2);
			if (c->map->map[x][y] == 'E')
				return (0);
			if (c->map->map[x][y] == 'W')
				return (M_PI);
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

double	normalize_angle(double ray)
{
	if (ray < 0)
		ray = ray + (2 * M_PI);
	if (ray > (2 * M_PI))
		ray = ray - (2 * M_PI);
	return (ray);
}

int	check_coli(t_core *c, double pos_x, double pos_y)
{
	if (c->map->map[(int)floor(pos_x) / 64][(int)floor(pos_y) / 64] == '1')
		return (0);
	else
		return (1);
}
