/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_3D.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:44:05 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/29 18:53:37 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	set_up_horizontal(t_rotation *rota, double ray, t_math *m)
{
	if (ray > M_PI && ray < 2 * M_PI)
	{
		m->x_step = -64;
		m->x_inter = (rota->p_x / 64) * 64 - 0.0001;
		m->y_inter = rota->p_y + (m->x_inter - rota->p_x) / tan(ray);
	}
	else
	{
		m->x_step = 64;
		m->x_inter = (rota->p_x / 64) * 64 + 64;
		m->y_inter = rota->p_y + (m->x_inter - rota->p_x) / tan(ray);
	}
	m->y_step = 64 / tan(ray);
}

double	check_horizontal_3d(t_core *c, t_rotation *rota, double ray)
{
	t_math	*m;
	double	end_value;

	m = malloc(sizeof(t_math));
	init_math(m);
	set_up_horizontal(rota, ray, m);
	while (m->x_inter > 0 && m->x_inter < c->map->height_line * 64
		&& m->y_inter > 0 && m->y_inter < c->map->lenght_line * 64)
	{
		m->map_x = (int)(m->x_inter / 64);
		m->map_y = (int)(m->y_inter / 64);
		if (c->map->map[m->map_x][m->map_y] == '1')
			break ;
		if (ray > M_PI && ray < 2 * M_PI)
			m->y_inter = m->y_inter - m->y_step;
		else
			m->y_inter = m->y_inter + m->y_step;
		m->x_inter = m->x_inter + m->x_step;
	}
	rota->hor_pos_wall_x = m->x_inter;
	rota->hor_pos_wall_y = m->y_inter;
	end_value = sqrt(pow(m->y_inter - rota->p_y, 2)
			+ pow(m->x_inter - rota->p_x, 2));
	free(m);
	return (end_value);
}

void	set_up_vertical(t_rotation *rota, double ray, t_math *m)
{
	if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
	{
		m->y_step = -64;
		m->y_inter = (rota->p_y / 64) * 64 - 0.0001;
		m->x_inter = rota->p_x + (m->y_inter - rota->p_y) * tan(ray);
	}
	else
	{
		m->y_step = 64;
		m->y_inter = (rota->p_y / 64) * 64 + 64;
		m->x_inter = rota->p_x + (m->y_inter - rota->p_y) * tan(ray);
	}
	m->x_step = 64 * tan(ray);
}

double	check_vertical_3d(t_core *c, t_rotation *rota, double ray)
{
	t_math	*m;
	double	end_value;

	m = malloc(sizeof(t_math));
	init_math(m);
	set_up_vertical(rota, ray, m);
	while (m->x_inter > 0 && m->x_inter < c->map->height_line * 64
		&& m->y_inter > 0 && m->y_inter < c->map->lenght_line * 64)
	{
		m->map_x = (int)(m->x_inter / 64);
		m->map_y = (int)(m->y_inter / 64);
		if (c->map->map[m->map_x][m->map_y] == '1')
			break ;
		if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
			m->x_inter = m->x_inter - m->x_step;
		else
			m->x_inter = m->x_inter + m->x_step;
		m->y_inter = m->y_inter + m->y_step;
	}
	rota->ver_pos_wall_x = m->x_inter;
	rota->ver_pos_wall_y = m->y_inter;
	end_value = sqrt(pow(m->y_inter - rota->p_y, 2)
			+ pow(m->x_inter - rota->p_x, 2));
	free(m);
	return (end_value);
}

void	send_ray_3d(t_core *c, t_rotation *rota, float current_ray)
{
	double	vertical_inter;
	double	horizontal_inter;

	horizontal_inter = check_horizontal_3d(c, rota, current_ray);
	vertical_inter = check_vertical_3d(c, rota, current_ray);
	if (vertical_inter < horizontal_inter)
	{
		rota->distance = vertical_inter;
		rota->hor_or_ver = 0;
	}
	else
	{
		rota->distance = horizontal_inter;
		rota->hor_or_ver = 1;
	}
}
