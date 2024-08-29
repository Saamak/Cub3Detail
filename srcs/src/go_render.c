/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:34:09 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/29 18:32:01 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	hit_wall(double x, double y, double ray, t_core *c)
{
	int	x_map;
	int	y_map;

	(void)ray;
	if (x < 0 || y < 0)
		return (1);
	x_map = floor(x / 64);
	y_map = floor(y / 64);
	if (x_map >= c->map->height_line || y_map >= c->map->lenght_line)
		return (1);
	if (c->map->map[x_map][y_map] == '1')
		return (1);
	return (0);
}

void	choose_wall(t_core *c, double start_pixel,
		double end_pixel, double current_ray)
{
	if (c->rota->hor_or_ver == 1)
	{
		if (current_ray > 0 && current_ray < M_PI)
			render_wall(c, start_pixel, end_pixel, c->img_s);
		else
			render_wall(c, start_pixel, end_pixel, c->img_n);
	}
	if (c->rota->hor_or_ver == 0)
	{
		if (current_ray > M_PI / 2 && current_ray < (3 * M_PI) / 2)
			render_wall(c, start_pixel, end_pixel, c->img_w);
		else
			render_wall(c, start_pixel, end_pixel, c->img_e);
	}
}

double	get_and_put_pix(t_core *c, double start_pixel, float x, void *img)
{
	int	color;

	if (c->rota->hor_or_ver == 0)
		color = mlx_get_image_pixel(c->mlx, img,
				(int)c->rota->ver_pos_wall_x % 64, (int)x);
	if (c->rota->hor_or_ver == 1)
		color = mlx_get_image_pixel(c->mlx, img,
				(int)c->rota->hor_pos_wall_y % 64, (int)x);
	if (c->rota->colone > 0 && c->rota->colone < 1280
		&& start_pixel > 0 && start_pixel < 720)
	{
		mlx_pixel_put(c->mlx, c->win,
			c->rota->colone, start_pixel, color);
	}
	return (start_pixel);
}

void	render_wall(t_core *c, double start_pixel, double end_pixel, void *img)
{
	float	x;
	float	steps;

	x = 64;
	steps = 64 / (start_pixel - end_pixel);
	if (start_pixel > 9500)
		start_pixel = 9500;
	if (end_pixel < 0)
		end_pixel = 0;
	while (start_pixel > end_pixel)
	{
		if (start_pixel <= 720 && start_pixel >= 0)
		{
			start_pixel = get_and_put_pix(c, start_pixel, x, img);
		}
		x = x - steps;
		start_pixel--;
	}
}

void	go_render(t_core *c)
{
	t_rotation	*rota;
	MLX_API int	mlx_mouse_hide();

	rota = malloc(sizeof(t_rotation));
	init_rota(rota, c);
	init_mlx(c);
	mlx_mouse_hide();
	c->rota = rota;
	put_image(c);
	cast_ray_3d(c);
	mlx_on_event(c->mlx, c->win, MLX_KEYDOWN, key_hook, c);
	mlx_on_event(c->mlx, c->win, MLX_WINDOW_EVENT, window_hook, c->mlx);
	mlx_loop(c->mlx);
	destroy_image(c);
	mlx_destroy_window(c->mlx, c->win);
	mlx_destroy_display(c->mlx);
	free(rota);
	return ;
}
