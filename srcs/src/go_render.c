/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:34:09 by pirulenc          #+#    #+#             */
/*   Updated: 2024/08/26 15:40:54 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int hit_wall(double x, double y, double ray, t_core *c)
{
    int x_map;
    int y_map;
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


void    pixel_draw(int x, int y, t_rotation *rota, t_core *c, int color)
{
    int j;
    int k;
    (void)rota;

    k = 0;
    j = 0;
    while (k <= 16)
    {
        while (j <= 16)
        {
            if (j == 0 || k == 0 || j == 16  || k == 16)
                mlx_pixel_put(c->mlx, c->win, (y * 16) + j, (x * 16) + k , 0xFF00c401);
            else if ((y * 16) + j == rota->p_y_2d && (x * 16) + k == rota->p_x_2d)
                mlx_pixel_put(c->mlx, c->win, (y * 16) + j, (x * 16) + k , 0xFF03eb00);
            else
                mlx_pixel_put(c->mlx, c->win, (y * 16) + j, (x * 16) + k , color);
            j++;
        }
        j = 0;
        k++;
    }
}

void    draw_minimap(t_rotation *rota, t_core *c)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (c->map->map[x])
    {
        while (c->map->map[x][y] && c->map->map[x][y] != '\n')
        {
            if (c->map->map[x][y] != '1')
                pixel_draw(x, y, rota, c, 0xFFffffff);
            else
                pixel_draw(x, y, rota, c, 0xFF002e6e);
            y++;
        }
        y = 0;
        x++;
    }
}

void    render_wall(t_core *c, int colone, double start_pixel, double end_pixel)
{
	int	color;
	float	x;
	float	steps;

	x = 64;
	steps = 64 / (start_pixel - end_pixel);
	//printf("steps = %f || height_wall = %f\n", steps, start_pixel - end_pixel);
    while (start_pixel > end_pixel)
	{
			if (c->rota->hor_or_ver == 0)
				color = mlx_get_image_pixel(c->mlx, c->img, (int)c->rota->ver_pos_wall_x % 64, (int)floor(x));
			if (c->rota->hor_or_ver == 1)
				color = mlx_get_image_pixel(c->mlx, c->img, (int)c->rota->hor_pos_wall_y % 64, (int)floor(x));
			mlx_pixel_put(c->mlx, c->win, colone, start_pixel--, color);
			x = x - (steps * 2);
			start_pixel--;
	}
        //mlx_pixel_put(c->mlx, c->win, colone, start_pixel--, 0xff9535ff);
}

void    render_floor_sky(t_core *c, int colone, double start_pixel, double end_pixel)
{
    int x;

    x = start_pixel;
    while (x < SCREEN_HEIGHT)
        mlx_pixel_put(c->mlx, c->win, colone, x++, 0xff058229);
    x = 0;
    while (x < end_pixel)
        mlx_pixel_put(c->mlx, c->win, colone, x++, 0xff00b7ef);
}
int check_collision(t_core *c, double pos_x, double pos_y)
{
    if (c->map->map[(int)floor(pos_x) / 64][(int)floor(pos_y) / 64] == '1')
        return (0);
    else
        return (1);
}

int key_hook(int key, void *tempo)
{
    t_core *c;

    c = (t_core *)tempo;
    if (key == 79)// fleche droite
    {
        c->rota->p_angle = normalize_angle(c->rota->p_angle + (0.01 * SPEED));
        cast_ray_3d(c);
    }
    else if (key == 80)// fleche gauche
    {
        c->rota->p_angle = normalize_angle(c->rota->p_angle - (0.01 * SPEED));
        cast_ray_3d(c);
    }
    else if (key == 26)// W move up
    {
        if (check_collision(c, c->rota->p_x + (sin(c->rota->p_angle) * SPEED), c->rota->p_y + (cos(c->rota->p_angle) * SPEED)) == 1
            && check_collision(c, c->rota->p_x + (sin(c->rota->p_angle) * SPEED), c->rota->p_y) == 1
            && check_collision(c, c->rota->p_x, c->rota->p_y + (cos(c->rota->p_angle) * SPEED)) == 1)
        {
            c->rota->p_x = c->rota->p_x + (sin(c->rota->p_angle) * SPEED);
            c->rota->p_y = c->rota->p_y + (cos(c->rota->p_angle) * SPEED);
            cast_ray_3d(c);
        }
    }
    else if (key == 22)// S move down
    {
        if (check_collision(c, c->rota->p_x + (-sin(c->rota->p_angle) * SPEED), c->rota->p_y + (-cos(c->rota->p_angle) * SPEED)) == 1
            && check_collision(c, c->rota->p_x + (-sin(c->rota->p_angle) * SPEED), c->rota->p_y) == 1
            && check_collision(c, c->rota->p_x, c->rota->p_y + (-cos(c->rota->p_angle) * SPEED)) == 1)
        {
            c->rota->p_x = c->rota->p_x + (-sin(c->rota->p_angle) * SPEED);
            c->rota->p_y = c->rota->p_y + (-cos(c->rota->p_angle) * SPEED);
            cast_ray_3d(c);
        }
    }
    else if (key == 4)// D move right
    {
        if (check_collision(c, c->rota->p_x + (-cos(c->rota->p_angle) * SPEED), c->rota->p_y + (sin(c->rota->p_angle) * SPEED)) == 1
            && check_collision(c, c->rota->p_x + (-cos(c->rota->p_angle) * SPEED), c->rota->p_y) == 1
            && check_collision(c, c->rota->p_x, c->rota->p_y + (sin(c->rota->p_angle) * SPEED)) == 1)
        {
            c->rota->p_x = c->rota->p_x + (-cos(c->rota->p_angle) * SPEED);
            c->rota->p_y = c->rota->p_y + (sin(c->rota->p_angle) * SPEED);
            cast_ray_3d(c);
        }
    }
    else if (key == 7)// A move left
    {
        if (check_collision(c, c->rota->p_x + (cos(c->rota->p_angle) * SPEED), c->rota->p_y + (-sin(c->rota->p_angle) * SPEED)) == 1
            && check_collision(c, c->rota->p_x + (cos(c->rota->p_angle) * SPEED), c->rota->p_y) == 1
            && check_collision(c, c->rota->p_x, c->rota->p_y + (-sin(c->rota->p_angle) * SPEED)) == 1)
        {
            c->rota->p_x = c->rota->p_x + (cos(c->rota->p_angle) * SPEED);
            c->rota->p_y = c->rota->p_y + (-sin(c->rota->p_angle) * SPEED);
            cast_ray_3d(c);
        }
    }
    return (0);
}

void    go_render(t_core *c)
{
    t_rotation  *rota;
	MLX_API int mlx_mouse_hide();

    rota = malloc(sizeof(t_rotation));
    init_rota(rota, c);
    init_mlx(c);
	mlx_mouse_hide();
    c->rota = rota;
	put_image(c);
    draw_minimap(rota, c);
    cast_ray_3d(c);
    mlx_on_event(c->mlx, c->win, MLX_KEYDOWN, key_hook, c);
	mlx_on_event(c->mlx, c->win, MLX_WINDOW_EVENT, window_hook, c->mlx);
    mlx_loop(c->mlx);
    mlx_destroy_window(c->mlx, c->win);
    mlx_destroy_display(c->mlx);
    free(rota);
    return ;
}
