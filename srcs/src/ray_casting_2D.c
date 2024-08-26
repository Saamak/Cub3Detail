/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_2D.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:41:38 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/26 16:02:16 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void    render_view(t_core *c, double current_ray, double pos_wall_x, double pos_wall_y)
{
    double  dx;
    double  dy;
    double  steps;
    double  x_inc;
    double  y_inc;
    double  x;
    double  y;
    int     i;

    (void)current_ray;
    i = 0;
    dx = pos_wall_x - c->rota->p_x_2d;
    dy = pos_wall_y - c->rota->p_y_2d;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    x_inc = dx / steps;
    y_inc = dy / steps;
    x = c->rota->p_x_2d;
    y = c->rota->p_y_2d;
    while (i < steps)
    {
        mlx_pixel_put(c->mlx, c->win, round(y), round(x), 0xff01ba05);
        x = x + x_inc;
        y = y + y_inc;
        i++;
    }
}

double  check_view(t_core *c, t_rotation *rota, double ray)
{
    double  x_inter;
    double  y_inter;

    (void)rota;
    (void)c;
    if (ray > M_PI && ray < 2 * M_PI)
    {
        x_inter = (rota->p_x_2d / 16) * 16 - 1;
        y_inter = rota->p_y_2d + (x_inter - rota->p_x_2d) / tan(ray);
    }
    else
    {
        x_inter = (rota->p_x_2d / 16) * 16 + 16;
        y_inter = rota->p_y_2d + (x_inter - rota->p_x_2d) / tan(ray);
    }
    render_view(c, ray, x_inter, y_inter);
    return (0);
}

//double  check_horizontal_2d(t_core *c, t_rotation *rota, double ray)
//{
//    double  x_inter;
//    double  y_inter;
//    double  x_step;
//    double  y_step;
//
//    (void)rota;
//    (void)c;
//    if (ray > M_PI && ray < 2 * M_PI)
//    {
//        x_step = -16;
//        x_inter = (rota->p_x_2d / 16) * 16 - 1;
//        y_inter = rota->p_y_2d + (x_inter - rota->p_x_2d) / tan(ray);
//    }
//    else
//    {
//        x_step = 16;
//        x_inter = (rota->p_x_2d / 16) * 16 + 16;
//        y_inter = rota->p_y_2d + (x_inter - rota->p_x_2d) / tan(ray);
//    }
//    y_step = 16 / tan(ray);
//    while (x_inter > 0 && x_inter < c->map->height_line * 16  && y_inter > 0 && y_inter < c->map->lenght_line * 16 && c->map->map[(int)(x_inter / 16)][(int)(y_inter / 16)] != '1')
//    {
//        if (ray > M_PI && ray < 2 * M_PI)
//            y_inter = y_inter - y_step;
//        else
//            y_inter = y_inter + y_step;
//        x_inter = x_inter + x_step;
//    }
//    rota->hor_pos_wall_x = x_inter;
//    rota->hor_pos_wall_y = y_inter;
//    return (sqrt(pow(y_inter - rota->p_y_2d, 2) + pow(x_inter - rota->p_x_2d, 2)));
//}

double  check_horizontal_2d(t_core *c, t_rotation *rota, double ray)
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
		x_step = -16;
		x_inter = (rota->p_x_2d / 16) * 16 - 0.0001;
		y_inter = rota->p_y_2d + (x_inter - rota->p_x_2d) / tan(ray);
	}
	else
	{
		x_step = 16;
		x_inter = (rota->p_x_2d / 16) * 16 + 16;
		y_inter = rota->p_y_2d + (x_inter - rota->p_x_2d) / tan(ray);
	}
	y_step = 16 / tan(ray);
	while (x_inter > 0 && x_inter < c->map->height_line * 16  && y_inter > 0 && y_inter < c->map->lenght_line * 16)
	{
		map_x = (int)(x_inter / 16);
		map_y = (int)(y_inter / 16);
		if (c->map->map[map_x][map_y] == '1')
			break ;
		if (ray > M_PI && ray < 2 * M_PI)
			y_inter = y_inter - y_step;
		else
			y_inter = y_inter + y_step;
		x_inter = x_inter + x_step;
	}
	rota->hor_pos_wall_x = x_inter;
	rota->hor_pos_wall_y = y_inter;
	return (sqrt(pow(y_inter - rota->p_y_2d, 2) + pow(x_inter - rota->p_x_2d, 2)));
}

//double  check_vertical_2d(t_core *c, t_rotation *rota, double ray)
//{
//    double  x_inter;
//    double  y_inter;
//    double  x_step;
//    double  y_step;
//
//    (void)rota;
//    (void)c;
//    if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
//    {
//        y_step = -16;
//        y_inter = (rota->p_y_2d / 16) * 16 - 1;
//        x_inter = rota->p_x_2d + (y_inter - rota->p_y_2d) * tan(ray);
//    }
//    else
//    {
//        y_step = 16;
//        y_inter = (rota->p_y_2d / 16) * 16 + 16;
//        x_inter = rota->p_x_2d + (y_inter - rota->p_y_2d) * tan(ray);
//    }
//    x_step = 16 * tan(ray);
//    while (x_inter > 0 && x_inter < c->map->height_line * 16  && y_inter > 0 && y_inter < c->map->lenght_line * 16 && c->map->map[(int)(x_inter / 16)][(int)(y_inter / 16)] != '1')
//    {
//        if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
//        {
//            x_inter = x_inter - x_step;
//        }
//        else
//            x_inter = x_inter + x_step;
//        y_inter = y_inter + y_step;
//    }
//    rota->ver_pos_wall_x = x_inter;
//    rota->ver_pos_wall_y = y_inter;
//    return (sqrt(pow(y_inter - rota->p_y_2d, 2) + pow(x_inter - rota->p_x_2d, 2)));
//}


double  check_vertical_2d(t_core *c, t_rotation *rota, double ray)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	int		map_x;
	int		map_y;

	(void)rota;
	(void)c;
	if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
	{
		y_step = -16;
		y_inter = (rota->p_y_2d / 16) * 16 - 0.0001;
		x_inter = rota->p_x_2d + (y_inter - rota->p_y_2d) * tan(ray);
	}
	else
	{
		y_step = 16;
		y_inter = (rota->p_y_2d / 16) * 16 + 16;
		x_inter = rota->p_x_2d + (y_inter - rota->p_y_2d) * tan(ray);
	}
	x_step = 16 * tan(ray);
	while (x_inter > 0 && x_inter < c->map->height_line * 16  && y_inter > 0 && y_inter < c->map->lenght_line * 16)
	{
		map_x = (int)(x_inter / 16);
		map_y = (int)(y_inter / 16);
		if (c->map->map[map_x][map_y] == '1')
			break ;
		if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
		{
			x_inter = x_inter - x_step;
		}
		else
			x_inter = x_inter + x_step;
		y_inter = y_inter + y_step;
	}
	rota->ver_pos_wall_x = x_inter;
	rota->ver_pos_wall_y = y_inter;
	return (sqrt(pow(y_inter - rota->p_y_2d, 2) + pow(x_inter - rota->p_x_2d, 2)));
}

void	send_ray_2d(t_core *c, t_rotation *rota, float current_ray)
{
	double	vertical_inter;
	double	horizontal_inter;

	horizontal_inter = check_horizontal_2d(c, rota, current_ray);
	vertical_inter = check_vertical_2d(c, rota, current_ray);
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

void	render_ray_2d(t_core *c, t_rotation *rota, double current_ray)
{
	double	dx;
	double	dy;
	double	steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	int		i;

	(void)current_ray;
	i = 0;
	if (rota->hor_or_ver == 0)
	{
		dx = rota->ver_pos_wall_x - rota->p_x_2d;
		dy = rota->ver_pos_wall_y - rota->p_y_2d;
	}
	if (rota->hor_or_ver == 1)
	{
		dx = rota->hor_pos_wall_x - rota->p_x_2d;
		dy = rota->hor_pos_wall_y - rota->p_y_2d;
	}
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = rota->p_x_2d;
	y = rota->p_y_2d;
	while (i < steps)
	{
		mlx_pixel_put(c->mlx, c->win, round(y), round(x), 0xffff0000);
		x = x + x_inc;
		y = y + y_inc;
		i++;
	}
}

void	cast_ray_2d(t_core *c)
{
	float	current_ray;
	float	angle_increment;
	int		nbr_ray;

	nbr_ray = 0;
	current_ray = normalize_angle(c->rota->p_angle + (c->rota->fov_rd / 2));
	angle_increment = c->rota->fov_rd / SCREEN_LENGHT;
	draw_minimap(c->rota, c);
	while (nbr_ray < SCREEN_LENGHT)
	{
		send_ray_2d(c, c->rota, current_ray);
		render_ray_2d(c, c->rota, current_ray);
		nbr_ray++;
		current_ray = normalize_angle(current_ray - angle_increment);
	}
	check_view(c, c->rota, c->rota->p_angle);
}
