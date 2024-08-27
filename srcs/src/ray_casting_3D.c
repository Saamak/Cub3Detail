/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_3D.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:44:05 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/27 17:41:37 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_math(t_math *math)
{
	math->x_inter = 0;
	math->y_inter = 0;
	math->x_step = 0;
	math->y_step = 0;
	math->map_x = 0;
	math->map_y = 0;
}

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

void	render_ray_3d(t_core *c, t_rotation *rota,
	double current_ray)
{
	double	wall;
	double	start_pixel;
	double	end_pixel;

	rota->distance = rota->distance * cos(current_ray - rota->p_angle);
	wall = (64 / rota->distance) * ((SCREEN_LENGHT / 2)
			/ tan(rota->fov_rd / 2));
	start_pixel = (SCREEN_HEIGHT / 2) + (wall / 2);
	end_pixel = (SCREEN_HEIGHT / 2) - (wall / 2);
	choose_wall(c, start_pixel, end_pixel, current_ray);
	render_floor_sky(c, start_pixel, end_pixel);
}

void	reset_screen(t_core *c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < SCREEN_LENGHT)
	{
		while (y < SCREEN_HEIGHT)
		{
			mlx_pixel_put(c->mlx, c->win, x, y, 0x00000000);
			y++;
		}
		y = 0;
		x++;
	}
}

void	cast_ray_3d(t_core *c)
{
	float	current_ray;
	float	angle_increment;

	reset_screen(c);
	current_ray = normalize_angle(c->rota->p_angle - (c->rota->fov_rd / 2));
	angle_increment = c->rota->fov_rd / SCREEN_LENGHT;
	while (c->rota->colone < SCREEN_LENGHT)
	{
		send_ray_3d(c, c->rota, current_ray);
		render_ray_3d(c, c->rota, current_ray);
		c->rota->colone++;
		current_ray = normalize_angle(current_ray + angle_increment);
	}
	c->rota->colone = 0;
}
