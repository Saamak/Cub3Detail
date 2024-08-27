/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_3D_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:08:49 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/27 18:15:14 by pirulenc         ###   ########.fr       */
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
