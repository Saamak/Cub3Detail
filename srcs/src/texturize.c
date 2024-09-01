/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirulenc <pirulenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:22:31 by ppitzini          #+#    #+#             */
/*   Updated: 2024/09/01 14:23:32 by pirulenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	verif_image_size(t_core *c, char *path)
{
	int		img_width;
	int		img_height;
	void	*img;

	img = mlx_png_file_to_image(c->mlx, path, &img_width, &img_height);
	if (img_width != 64 || img_height != 64)
	{
		printf("Error\nTexture %s is not 64x64\n", path);
		mlx_destroy_image(c->mlx, img);
		return (0);
	}
	mlx_destroy_image(c->mlx, img);
	return (1);
}

int	verif__all_image_size(t_core *c)
{
	if (!verif_image_size(c, c->texture->no))
		return (0);
	if (!verif_image_size(c, c->texture->ea))
		return (0);
	if (!verif_image_size(c, c->texture->so))
		return (0);
	if (!verif_image_size(c, c->texture->we))
		return (0);
	return (1);
}

int	put_image(t_core *c)
{
	int	img_width;
	int	img_height;

	img_height = 64;
	img_width = 64;
	if (verif__all_image_size(c) == 0)
		return (0);
	c->img_n = mlx_png_file_to_image(c->mlx, c->texture->no,
			&img_width, &img_height);
	c->img_e = mlx_png_file_to_image(c->mlx, c->texture->ea,
			&img_width, &img_height);
	c->img_s = mlx_png_file_to_image(c->mlx, c->texture->so,
			&img_width, &img_height);
	c->img_w = mlx_png_file_to_image(c->mlx, c->texture->we,
			&img_width, &img_height);
	return (1);
}
