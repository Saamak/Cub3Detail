/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:34:09 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/29 06:27:07 by pirulenc         ###   ########.fr       */
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
                return ((3 * M_PI) / 2);
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
    rota->ver_pos_wall_x = 0;
    rota->ver_pos_wall_y = 0;
    rota->hor_pos_wall_x = 0;
    rota->hor_pos_wall_y = 0;
    rota->hor_or_ver = 0;
    rota->distance = 0;
}

void    init_mlx(t_core *c)
{
    c->mlx = mlx_init();
    c->win = mlx_new_window(c->mlx, SCREEN_LENGHT, SCREEN_HEIGHT, "Cub3D");
}
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

double  normalize_angle(double ray)
{
    if (ray < 0)
        ray = ray + (2 * M_PI);
    if (ray > (2 * M_PI))
        ray = ray - (2 * M_PI);
    return (ray);
}

double  check_horizontal(t_core *c, t_rotation *rota, double ray)
{
    double  x_inter;
    double  y_inter;
    double  x_step;
    double  y_step;

    (void)rota;
    (void)c;
    if (ray > M_PI && ray < 2 * M_PI)
    {
        x_step = -64;
        x_inter = (rota->p_x / 64) * 64 - 1;
        y_inter = rota->p_y + (x_inter - rota->p_x) / tan(ray);
    }
    else
    {
        x_step = 64;
        x_inter = (rota->p_x / 64) * 64 + 64;
        y_inter = rota->p_y + (x_inter - rota->p_x) / tan(ray);
    }
    y_step = 64 / tan(ray);
    while (x_inter > 0 && x_inter < c->map->height_line * 64  && y_inter > 0 && y_inter < c->map->lenght_line * 64 && c->map->map[(int)(x_inter / 64)][(int)(y_inter / 64)] != '1')
    {
        if (ray > M_PI && ray < 2 * M_PI)
            y_inter = y_inter - y_step;
        else
            y_inter = y_inter + y_step;
        x_inter = x_inter + x_step;
    }
    //printf("HORIZONTAL ==> x_inter = %f || y_inter = %f\n\n", x_inter, y_inter);
    rota->hor_pos_wall_x = x_inter; 
    rota->hor_pos_wall_y = y_inter;
    //printf("HORIZONTAL ==> x_inter = %f || y_inter = %f\n\n", x_inter, y_inter);
    return (sqrt(pow(y_inter - rota->p_y, 2) + pow(x_inter - rota->p_x, 2)));
}

double  check_vertical(t_core *c, t_rotation *rota, double ray)
{
    double  x_inter;
    double  y_inter;
    double  x_step;
    double  y_step;

    (void)rota;
    (void)c;
    if (ray > M_PI / 2 && ray < 3 * M_PI / 2)
    {
        y_step = -64;
        y_inter = (rota->p_y / 64) * 64 - 1;
        x_inter = rota->p_x + (y_inter - rota->p_y) * tan(ray);
    }
    else
    {
        y_step = 64;
        y_inter = (rota->p_y / 64) * 64 + 64;
        x_inter = rota->p_x + (y_inter - rota->p_y) * tan(ray);
    }
    x_step = 64 * tan(ray);
    while (x_inter > 0 && x_inter < c->map->height_line * 64  && y_inter > 0 && y_inter < c->map->lenght_line * 64 && c->map->map[(int)(x_inter / 64)][(int)(y_inter / 64)] != '1')
    {
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
    return (sqrt(pow(y_inter - rota->p_y, 2) + pow(x_inter - rota->p_x, 2)));
}

void    send_ray(t_core *c, t_rotation *rota, float current_ray)
{
    double  vertical_inter;
    double  horizontal_inter;

    horizontal_inter = check_horizontal(c, rota, current_ray);
    vertical_inter = check_vertical(c, rota, current_ray);
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
void    render_ray_2d(t_core *c, t_rotation *rota, double current_ray)
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
    if (rota->hor_or_ver == 0)
    {
        dx = rota->ver_pos_wall_x - rota->p_x;
        dy = rota->ver_pos_wall_y - rota->p_y;
    }
    if (rota->hor_or_ver == 1)
    {
        dx = rota->hor_pos_wall_x - rota->p_x;
        dy = rota->hor_pos_wall_y - rota->p_y;
    }
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    x_inc = dx / steps;
    y_inc = dy / steps;
    x = rota->p_x;
    y = rota->p_y;
    while (i < steps)
    {   
        mlx_pixel_put(c->mlx, c->win, round(y), round(x), 0xffff0000);
        x = x + x_inc;
        y = y + y_inc;
        i++;
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

void    render_ray_3d(t_core *c, t_rotation *rota, double current_ray, int colone)
{
    double  wall;
    double  start_pixel;
    double  end_pixel;

    rota->distance = rota->distance * cos(current_ray - rota->p_angle);
    wall = (64 / rota->distance) * ((SCREEN_LENGHT / 2) / tan(rota->fov_rd / 2));
    start_pixel = (SCREEN_HEIGHT / 2) + (wall / 2);
    end_pixel = (SCREEN_HEIGHT / 2) - (wall / 2);
    if (start_pixel > SCREEN_HEIGHT)
        start_pixel = SCREEN_HEIGHT;
    if (end_pixel < 0)
        end_pixel = 0;
    render_wall(c, colone, start_pixel, end_pixel);
    render_floor_sky(c, colone, start_pixel, end_pixel);
}

void    cast_ray_2d(t_core *c)
{
    float   current_ray;
    float   angle_increment;
    int     nbr_ray;
    
    nbr_ray = 0;
    current_ray = normalize_angle(c->rota->p_angle + (c->rota->fov_rd / 2));
    angle_increment = c->rota->fov_rd / SCREEN_LENGHT;
    draw_minimap(c->rota, c);
    while (nbr_ray < SCREEN_LENGHT)//current_ray >= normalize_angle(c->rota->p_angle - (c->rota->fov_rd / 2)))
    {
        //if (nbr_ray == 1)// || nbr_ray == SCREEN_LENGHT)
        //{
            //printf("\n\n===>> angle = %f <<===\n\n", current_ray);
            //c->rota->p_angle = normalize_angle(c->rota->p_angle);
            send_ray(c, c->rota, current_ray);
            render_ray_2d(c, c->rota, current_ray);
            //render_ray_3d(c, c->rota, current_ray, nbr_ray);
        //}
        nbr_ray++;
        current_ray = normalize_angle(current_ray - angle_increment);
    }
}

void    cast_ray_3d(t_core *c)
{
    float   current_ray;
    float   angle_increment;
    int     nbr_ray;
    
    nbr_ray = 0;
    current_ray = normalize_angle(c->rota->p_angle + (c->rota->fov_rd / 2));
    angle_increment = c->rota->fov_rd / SCREEN_LENGHT;
    while (nbr_ray < SCREEN_LENGHT)//current_ray >= normalize_angle(c->rota->p_angle - (c->rota->fov_rd / 2)))
    {
        //if (nbr_ray == 1)// || nbr_ray == SCREEN_LENGHT)
        //{
            //printf("\n\n===>> angle = %f <<===\n\n", current_ray);
            //c->rota->p_angle = normalize_angle(c->rota->p_angle);
            send_ray(c, c->rota, current_ray);
            //render_ray_2d(c, c->rota, current_ray);
            render_ray_3d(c, c->rota, current_ray, nbr_ray);
        //}
        nbr_ray++;
        current_ray = normalize_angle(current_ray - angle_increment);
    }
    cast_ray_2d(c);
}

int key_hook(int key, void *tempo)
{
    t_core *c;

    c = (t_core *)tempo;
    if (key == 79)// fleche droite
    {
        c->rota->p_angle = normalize_angle(c->rota->p_angle + (0.01 * SPEED));
        //draw_minimap(c->rota, c);
        cast_ray_3d(c);
    }
    else if (key == 80)// fleche gauche
    {
        c->rota->p_angle = normalize_angle(c->rota->p_angle - (0.01 * SPEED));
        //draw_minimap(c->rota, c);
        cast_ray_3d(c);
    }
    else if (key == 26)// W move up
    {
        c->rota->p_x = c->rota->p_x + (sin(c->rota->p_angle) * SPEED);
        c->rota->p_y = c->rota->p_y + (cos(c->rota->p_angle) * SPEED);
        //draw_minimap(c->rota, c);
        cast_ray_3d(c);
    }
    else if (key == 22)// S move down
    {
        c->rota->p_x = c->rota->p_x + (-sin(c->rota->p_angle) * SPEED);
        c->rota->p_y = c->rota->p_y + (-cos(c->rota->p_angle) * SPEED);
        //draw_minimap(c->rota, c);
        cast_ray_3d(c);
    }
    else if (key == 7)// D move right
    {
        c->rota->p_x = c->rota->p_x + (cos(c->rota->p_angle) * SPEED);
        c->rota->p_y = c->rota->p_y + (-sin(c->rota->p_angle) * SPEED);
        //draw_minimap(c->rota, c);
        cast_ray_3d(c);
    }
    else if (key == 4)// A move left
    {
        c->rota->p_x = c->rota->p_x + (-cos(c->rota->p_angle) * SPEED);
        c->rota->p_y = c->rota->p_y + (sin(c->rota->p_angle) * SPEED);
        //draw_minimap(c->rota, c);
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