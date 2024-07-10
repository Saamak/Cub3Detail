/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:34:09 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/10 20:30:16 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int get_scale_minimap(t_core *c, int x)
{
    if (x == 1)
    {
        if (c->map->lenght_line <= 30)
            return (15);
        if (c->map->lenght_line >= 30 && c->map->lenght_line <= 60)
            return (15);
        else
            return (3);
    }
    if (x == 2)
    {
        if (c->map->height_line <= 30)
            return (15);
        if (c->map->height_line >= 30 && c->map->height_line <= 60)
            return (15);
        else
            return (3);
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
    scale_hor = get_scale_minimap(c, 1);
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

void    draw_player(int color, int x, int y, void *mlx, void *win, t_core *c, t_rotation *rota)
{
    int scale_hor;
    int scale_haut;
    int i;
    int j;

    (void)rota;
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
            if (((j + (x * scale_haut)) == rota->pix_x && (i + (y * scale_hor)) == rota->pix_y)
                || ((j + (x * scale_haut)) == (rota->pix_x - 1) && (i + (y * scale_hor)) == (rota->pix_y))
                || ((j + (x * scale_haut)) == (rota->pix_x - 1) && (i + (y * scale_hor)) == (rota->pix_y - 1))
                || ((j + (x * scale_haut)) == (rota->pix_x) && (i + (y * scale_hor)) == (rota->pix_y - 1)))
                mlx_pixel_put(mlx, win, (j + (y * scale_haut)), (i + (x * scale_hor)), color);
            else
               mlx_pixel_put(mlx, win, (j + (y * scale_haut)), (i + (x * scale_hor)), 0xFF5f5f5f);
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

void    render_minimap(t_core *c, void *mlx, void *win, t_rotation *rota)
{
    int x;
    int y;
    int color;

    (void)mlx;
    (void)win;
    (void)rota;
    x = 0;
    y = 0;
    while (x < c->map->height_line)
    {
        while (c->map->map[x][y] && c->map->map[x][y] != '\n')
        {
            color = select_one_wall(x, y, c);
            if (c->map->map[x][y] == 'N' || c->map->map[x][y] == 'E' || c->map->map[x][y] == 'W' || c->map->map[x][y] == 'S')
                draw_player(color, x, y, mlx, win, c, rota);
            else    
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

void    draw_line(t_core *c, t_rotation *rota)
{
    double  x;
    double  y;
    double  d_x;
    double  d_y;
    double  m;
    int  ligne_y;
    int  ligne_x;

    y = sin(rota->angle_c);
    x = cos(rota->angle_c);
    printf("MAP LENGHT (x) = %d || MAP HEIGJT (y) = %d\n", (c->map->lenght_line * TILE), (TILE * c->map->height_line));
    printf("A ==>(y) = %d ||(x) = %d\n", rota->pix_y, rota->pix_x);
    printf("B ==>(y) = %f ||(x) = %f\n", y, x);
    d_x = rota->pix_x - x;  
    d_y = rota->pix_y - y;
    m = d_y / d_x;
    ligne_y = 1;
    ligne_x = rota->pix_x;
    while (ligne_x < x)
    {
        ligne_y = rota->pix_y + (m * (ligne_x - rota->pix_x));
        mlx_pixel_put(c->mlx, c->win, ligne_y, ligne_x, 0xFF0059ff);
        ligne_x++;
    }
}

void    go_render(t_core *c)
{
    int x;
    int y;
    t_rotation  *rota;

    rota = NULL;
    x = 0;
    y = 0;
    c->mlx = mlx_init();
    c->win = mlx_new_window(c->mlx, 1280, 720, "test");
    rota = start_rotation(c);
    render_minimap(c, c->mlx, c->win, rota);
    mlx_pixel_put(c->mlx, c->win, rota->pix_y, rota->pix_x, 0xFF0059ff);
    //draw_line(c, rota);
    mlx_loop(c->mlx);
    mlx_destroy_window(c->mlx, c->win);
    mlx_destroy_display(c->mlx);
    free(rota);
}