/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:34:09 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/29 06:52:36 by pirulenc         ###   ########.fr       */
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
    while (k <= 64)
    {
        while (j <= 64)
        {
            if (j == 0 || k == 0 || j == 64  || k == 64)
                mlx_pixel_put(c->mlx, c->win, (y * 64) + j, (x * 64) + k , 0xFF00c401);
            else if ((y * 64) + j == rota->p_y && (x * 64) + k == rota->p_x)
                mlx_pixel_put(c->mlx, c->win, (y * 64) + j, (x * 64) + k , 0xFF03eb00);
            else
                mlx_pixel_put(c->mlx, c->win, (y * 64) + j, (x * 64) + k , color);
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
    while (start_pixel > end_pixel)
        mlx_pixel_put(c->mlx, c->win, colone, start_pixel--, 0xff9535ff);
}

void    render_floor_sky(t_core *c, int colone, double start_pixel, double end_pixel)
{
    int x;

    x = start_pixel;
    while (x < SCREEN_HEIGHT)
        mlx_pixel_put(c->mlx, c->win, colone, x++, 0xff01ba05);
    x = 0;
    while (x < end_pixel)
        mlx_pixel_put(c->mlx, c->win, colone, x++, 0xff01bab9);
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
        c->rota->p_x = c->rota->p_x + (sin(c->rota->p_angle) * SPEED);
        c->rota->p_y = c->rota->p_y + (cos(c->rota->p_angle) * SPEED);
        cast_ray_3d(c);
    }
    else if (key == 22)// S move down
    {
        c->rota->p_x = c->rota->p_x + (-sin(c->rota->p_angle) * SPEED);
        c->rota->p_y = c->rota->p_y + (-cos(c->rota->p_angle) * SPEED);
        cast_ray_3d(c);
    }
    else if (key == 7)// D move right
    {
        c->rota->p_x = c->rota->p_x + (cos(c->rota->p_angle) * SPEED);
        c->rota->p_y = c->rota->p_y + (-sin(c->rota->p_angle) * SPEED);
        cast_ray_3d(c);
    }
    else if (key == 4)// A move left
    {
        c->rota->p_x = c->rota->p_x + (-cos(c->rota->p_angle) * SPEED);
        c->rota->p_y = c->rota->p_y + (sin(c->rota->p_angle) * SPEED);
        cast_ray_3d(c);
    }
    return (0);
}

void    go_render(t_core *c)
{
    t_rotation  *rota;

    rota = malloc(sizeof(t_rotation));
    init_rota(rota, c);
    init_mlx(c);
    c->rota = rota;
    draw_minimap(rota, c);
    cast_ray_3d(c);
    mlx_on_event(c->mlx, c->win, MLX_KEYDOWN, key_hook, c);
    mlx_loop(c->mlx);
    mlx_destroy_window(c->mlx, c->win);
    mlx_destroy_display(c->mlx);
    free(rota);
    return ;
}