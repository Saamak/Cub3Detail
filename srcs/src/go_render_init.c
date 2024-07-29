/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_render_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:40:32 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/29 06:41:03 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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