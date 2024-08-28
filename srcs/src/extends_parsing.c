/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extends_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:10:11 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/28 18:04:07 by pirulenc         ###   ########.fr       */
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
		if (c->map->w_e)
			textures_error_alloc(c);
		else
			return (test_it(line, c, 3));
	}
	else if ((*line == 'E' && *(line + 1) == 'A')
		|| (*line == 'E' && *(line + 1) == ' '))
	{
		if (c->map->e_a)
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

void	render_floor_sky(t_core *c,
	double start_pixel, double end_pixel)
{
	int	x;

	x = start_pixel;
	while (x < SCREEN_HEIGHT)
		mlx_pixel_put(c->mlx, c->win, c->rota->colone, x++, c->texture->rgb_c);
	x = 0;
	while (x < end_pixel)
		mlx_pixel_put(c->mlx, c->win, c->rota->colone, x++, c->texture->rgb_f);
}

void	key_escape(t_core *c)
{
	mlx_destroy_window(c->mlx, c->win);
	mlx_loop_end(c->mlx);
	return ;
}
