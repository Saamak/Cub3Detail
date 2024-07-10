/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:44:28 by pirulenc          #+#    #+#             */
/*   Updated: 2024/07/10 19:21:52 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void    pos_player(t_rotation *rota, t_core *c)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (c->map->map[x][y])
    {
        while (c->map->map[x][y] && c->map->map[x][y] != '\n')
        {
            if (c->map->map[x][y] == 'N')
            {
                rota->angle_c = M_PI / 2;
                rota->angle_l = (2 * M_PI) / 3;
                rota->angle_r = M_PI / 3;
            }
            if (c->map->map[x][y] == 'S')
            {
                rota->angle_c = (3 * M_PI) / 2;
                rota->angle_l = (5 * M_PI) / 3;
                rota->angle_r = (4 * M_PI) / 3;
            }
            if (c->map->map[x][y] == 'E')
            {
                rota->angle_c = 2 * M_PI;
                rota->angle_l = M_PI / 6;
                rota->angle_r = (11 * M_PI) / 6;
            }
            if (c->map->map[x][y] == 'W')
            {
                rota->angle_c = M_PI;
                rota->angle_l = (7 * M_PI) / 6;
                rota->angle_r = (5 * M_PI) / 6;
            }
            if (c->map->map[x][y] == 'N' || c->map->map[x][y] == 'S' || c->map->map[x][y] == 'E' || c->map->map[x][y] == 'W')
            {
                rota->p_x = x;
                rota->p_y = y;
                rota->fov_rd = (FOV * M_PI) / 180;
                return ;
            }
            y++;
        }
        y = 0;
        x++;
    }
    return ;
}

void    init_rota(t_rotation *rota, t_core *c)
{
    pos_player(rota, c);
    rota->pix_x = (rota->p_x * TILE) + (TILE / 2);
    rota->pix_y = (rota->p_y * TILE) + (TILE / 2);
    printf("pos player x = %d || y = %d\n pos player pixel x = %d || y = %d\n", rota->p_x, rota->p_y, rota->pix_x, rota->pix_y);
    printf("angle start = %f || fov_rd = %f\n", rota->angle_c, rota->fov_rd);
}

t_rotation  *start_rotation(t_core *c)
{
    t_rotation *rota;
    
    rota = malloc(sizeof(t_rotation *));
    if (!rota)
        return (NULL);
    init_rota(rota, c);
    return (rota);
}