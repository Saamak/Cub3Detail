/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:34:09 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/08 16:18:47 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int get_scale_minimap(t_core *c, int x)
{
    if (x == 1)
    {
        if (c->map->lenght_line <= 30)
            return (10);
        if (c->map->lenght_line >= 30 && c->map->lenght_line <= 60)
            return (5);
        else
            return (2);
    }
    if (x == 2)
    {
        if (c->map->height_line <= 30)
            return (10);
        if (c->map->height_line >= 30 && c->map->height_line <= 60)
            return (5);
        else
            return (2);
    }
    return (0);
}

void    draw_onw_wall(int color, int x, int y, void *mlx, void *win, t_core *c)
{
    int scale_hor;
    int scale_haut;
    int i;
    int j;

    i = 0;
    j = 0;
    scale_hor = get_scale_minimap(c, 1);\
    //printf("scale_hor =  %d\n", scale_hor);
    scale_haut = get_scale_minimap(c, 2);
    //printf("scale haut =  %d\n", scale_haut);
    while (j + (x * scale_haut) <= (x * scale_haut) + scale_haut)
    {
        while (i + (y * scale_hor) < (y * scale_hor) + scale_hor)
        {
            mlx_pixel_put(mlx, win, (j + (y * scale_haut)), (i + (x * scale_hor)), color);
            i++;
        }
        i = 0;
        j++;
    }
}

int select_one_wall(int x, int y, t_core *c)
{
    int color;

    if (c->map->map[x][y] == ' ')
        color = 0xFF000000;
    else if (c->map->map[x][y] == '1')
        color = 0xffff0000;
    else if (c->map->map[x][y] == '0')
        color = 0xFF5f5f5f;
    else
        color = 0xFFfbff00;
   return (color);
}

void    render_minimap(t_core *c, void *mlx, void *win)
{
    int x;
    int y;
    int color;

    (void)mlx;
    (void)win;
    x = 0;
    y = 0;
    while (x < c->map->height_line)
    {
        while (c->map->map[x][y] != '\n')
        {
            color = select_one_wall(x, y, c);
            draw_onw_wall(color, x, y, mlx, win, c);
            y++;
        }
        y = 0;
        x++;
    }
}

int win_hook(int event, void *mlx)
{
    if (event == 0)
        mlx_loop_end(mlx);
    return (0);
}

void    detect_input(t_core *c, void *mlx, void *win)
{
    (void)c;
    mlx_on_event(mlx, win, MLX_WINDOW_EVENT, win_hook, mlx);
}

void    go_render(t_core *c)
{
    int x;
    int y;

    x = 0;
    y = 0;
    c->mlx = mlx_init();
    c->win = mlx_new_window(c->mlx, 1280, 720, "test");
    render_minimap(c, c->mlx, c->win);
    start_rotation(c);
    mlx_loop(c->mlx);
    mlx_destroy_window(c->mlx, c->win);
    mlx_destroy_display(c->mlx);
}
