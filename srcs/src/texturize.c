/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:22:31 by ppitzini          #+#    #+#             */
/*   Updated: 2024/08/03 02:27:57 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	put_image(t_core *c)
{
	int img_width;
	int img_height;

	img_height = 64;
	img_width = 64;
	c->img = mlx_png_file_to_image(c->mlx, "srcs/textures/mouton.png", &img_width, &img_height);

	 // displays the image at x,y = 42,42

	// mlx_destroy_image(c->mlx, img);
	// mlx_destroy_display(c->mlx);
}
