/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_3D.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:44:05 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/27 02:31:31 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

double  check_horizontal_3d(t_core *c, t_rotation *rota, double ray)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	int		map_x;
	int		map_y;

	(void)rota;
	(void)c;
	if (ray > M_PI && ray < 2 * M_PI)
	{
		x_step = -64;
		x_inter = (rota->p_x / 64) * 64 - 0.0001;
		y_inter = rota->p_y + (x_inter - rota->p_x) / tan(ray);
	}
	else
	{
		x_step = 64;
		x_inter = (rota->p_x / 64) * 64 + 64;
		y_inter = rota->p_y + (x_inter - rota->p_x) / tan(ray);
	}
	y_step = 64 / tan(ray);
	while (x_inter > 0 && x_inter < c->map->height_line * 64
		&& y_inter > 0 && y_inter < c->map->lenght_line * 64)
	{
		map_x = (int)(x_inter / 64);
		map_y = (int)(y_inter / 64);
		if (c->map->map[map_x][map_y] == '1')
			break;
		if (ray > M_PI && ray < 2 * M_PI)
			y_inter = y_inter - y_step;
		else
			y_inter = y_inter + y_step;
		x_inter = x_inter + x_step;
	}
	rota->hor_pos_wall_x = x_inter;
	rota->hor_pos_wall_y = y_inter;
	return (sqrt(pow(y_inter - rota->p_y, 2) + pow(x_inter - rota->p_x, 2)));
	}

	double  check_vertical_3d(t_core *c, t_rotation *rota, double ray)
	{
	double  x_inter;
	double  y_inter;
	double  x_step;
	double  y_step;
	int     map_x;
	int     map_y;

	(void)rota;
	(void)c;
	if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
	{
		y_step = -64;
		y_inter = (rota->p_y / 64) * 64 - 0.0001;
		x_inter = rota->p_x + (y_inter - rota->p_y) * tan(ray);
	}
	else
	{
		y_step = 64;
		y_inter = (rota->p_y / 64) * 64 + 64;
		x_inter = rota->p_x + (y_inter - rota->p_y) * tan(ray);
	}
	x_step = 64 * tan(ray);
	while (x_inter > 0 && x_inter < c->map->height_line * 64
		&& y_inter > 0 && y_inter < c->map->lenght_line * 64)
	{
		map_x = (int)(x_inter / 64);
		map_y = (int)(y_inter / 64);
		if (c->map->map[map_x][map_y] == '1')
			break;
		if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
			x_inter = x_inter - x_step;
		else
			x_inter = x_inter + x_step;
		y_inter = y_inter + y_step;
	}
	rota->ver_pos_wall_x = x_inter;
	rota->ver_pos_wall_y = y_inter;
	return (sqrt(pow(y_inter - rota->p_y, 2) + pow(x_inter - rota->p_x, 2)));
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
	wall = (64 / rota->distance) * ((SCREEN_LENGHT / 2) / tan(rota->fov_rd / 2));
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
	//cast_ray_2d(c);
	//mlx_put_image_to_window(c->mlx, c->win, c->img, 0, 0);
}
