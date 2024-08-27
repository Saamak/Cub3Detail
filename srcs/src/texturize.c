/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:22:31 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/27 17:42:00 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	put_image(t_core *c)
{
	int	img_width;
	int	img_height;

	img_height = 64;
	img_width = 64;
	c->img_n = mlx_png_file_to_image(c->mlx, "srcs/textures/mouton.png",
			&img_width, &img_height);
	c->img_e = mlx_png_file_to_image(c->mlx, "srcs/textures/nothing_here.png",
			&img_width, &img_height);
	c->img_s = mlx_png_file_to_image(c->mlx, "srcs/textures/bobby.png",
			&img_width, &img_height);
	c->img_w = mlx_png_file_to_image(c->mlx, "srcs/textures/cow.png",
			&img_width, &img_height);
}
