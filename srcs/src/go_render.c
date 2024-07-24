/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:34:09 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/24 09:47:31 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int get_pos_player_x(t_core *c)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < c->map->height_line)
    {
        while (c->map->map[x][y])
        {
            if (c->map->map[x][y] == 'N' || c->map->map[x][y] == 'S'
                || c->map->map[x][y] == 'E' || c->map->map[x][y] == 'W')
            {
                printf("x = %d\n", x);
                return (x * 64 + 32);
            }
            y++;
        }
        y = 0;
        x++;
    }
    return (0);
}

int get_pos_player_y(t_core *c)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < c->map->height_line)
    {
        while (c->map->map[x][y])
        {
            if (c->map->map[x][y] == 'N' || c->map->map[x][y] == 'S'
                || c->map->map[x][y] == 'E' || c->map->map[x][y] == 'W')
            {
                printf("y = %d\n", y);
                return (y * 64 + 32);
            }
            y++;
        }
        y = 0;
        x++;
    }
    return (0);
}

double  get_angle_player(t_core *c)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < c->map->height_line)
    {
        while (c->map->map[x][y])
        {
            if (c->map->map[x][y] == 'N')
                return (3 * M_PI / 2);
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

void    init_rota(t_rotation *rota, t_core *c)
{
    rota->p_angle = get_angle_player(c);
    rota->p_x = get_pos_player_x(c);
    rota->p_y = get_pos_player_y(c);
    rota->fov_rd = FOV * M_PI / 180;
    rota->ray_step = FOV / SCREEN_LENGHT;
}

void    init_mlx(t_core *c)
{
    c->mlx = mlx_init();
    c->win = mlx_new_window(c->mlx, SCREEN_LENGHT, SCREEN_HEIGHT, "Cub3D");
}

void    send_ray(t_core *c, t_rotation *rota, float current_ray)
{
    float   f_x;
    float   f_y;
    float   x_step;
    float   y_step;
    int     hit;
    float   current_pos_x;
    int     int_current_pos_x;
    float   current_pos_y;
    int     int_current_pos_y;

    (void)c;
    hit = 0;
    f_y = (rota->p_y / 64) * 64;
    f_x = rota->p_x + (f_y - rota->p_y) / tan(current_ray);
    y_step = 64;
    x_step = 64 / tan(current_ray);
    current_pos_x = f_x;
    int_current_pos_x = (int)current_pos_x;
    current_pos_y = f_y;
    printf("test p_y = %f\n", f_x);
    int_current_pos_y = (int)current_pos_y;
    printf("case player x = %d|| case player y = %d |||| check case x = %d || check case y = %d\n", (int)rota->p_x / 64, (int)rota->p_y / 64, int_current_pos_x / 64, int_current_pos_y / 64);
    if (int_current_pos_x / 64 < c->map->height_line && int_current_pos_y / 64 < c->map->lenght_line && c->map->map[int_current_pos_x / 64][int_current_pos_y / 64] == '1')
    {
        hit = 1;
        //printf("wall hit position x = %d || y = %d\n", int_current_pos_x / 64, int_current_pos_y / 64);
        return ;
    }
    while (!hit)
    {
        current_pos_x = current_pos_x + x_step;
        int_current_pos_x = (int)current_pos_x;
        current_pos_y = current_pos_y + y_step;
        int_current_pos_y = (int)current_pos_y;
        if (int_current_pos_x / 64 < c->map->height_line && int_current_pos_y / 64 < c->map->lenght_line && c->map->map[int_current_pos_x / 64][int_current_pos_y / 64] == '1')
        {
            hit = 1;
            //printf("wall hit position x = %d || y = %d\n", int_current_pos_x / 64, int_current_pos_y / 64);
        }
    }
}

void    pixel_draw(int x, int y, t_rotation *rota, t_core *c, int color)
{
    int j;
    int k;
    int pos_player_x;
    int pos_player_y;

    (void)rota;
    k = 0;
    j = 0;
    pos_player_x = ((rota->p_x - 32) / 64) * 15 + 7;
    pos_player_y = ((rota->p_y - 32) / 64) * 15 + 7;
    while (k <= 15)
    {
        while (j <= 15)
        {
            if ((x * 15) + j == pos_player_x && (y * 15) + k == pos_player_y)
                mlx_pixel_put(c->mlx, c->win, (y * 15) + k, (x * 15) + j , 0xFF03eb00);
            else
                mlx_pixel_put(c->mlx, c->win, (y * 15) + k, (x * 15) + j , color);
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
        while (c->map->map[x][y])
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

void    go_render(t_core *c)
{
    t_rotation *rota;
    float   current_ray;
    float   angle_increment;

    rota = malloc(sizeof(t_rotation));
    init_rota(rota, c);
    init_mlx(c);
    printf("%f\n", M_PI);
    printf("ROTA == p_x = %d || p_y = %d || p_angle = %f || ray_step = %f\n", rota->p_x, rota->p_y, rota->p_angle, rota->ray_step);
    current_ray = rota->p_angle - rota->fov_rd / 2;
    angle_increment = (current_ray + rota->fov_rd) / SCREEN_LENGHT;
    printf("first ray = %f\n", current_ray);
    while (current_ray < rota->p_angle + rota->fov_rd / 2)
    {
        send_ray(c, rota, current_ray);
        current_ray = current_ray + angle_increment;
    }
    draw_minimap(rota, c);
    mlx_loop(c->mlx);
    mlx_destroy_window(c->mlx, c->win);
    mlx_destroy_display(c->mlx);
    free(rota);
    return ;
}