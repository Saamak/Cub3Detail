/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verifs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:22:08 by ppitzini          #+#    #+#             */
/*   Updated: 2024/07/08 17:48:39 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ac_checks(int ac)
{
	if (ac != 2)
	{
		return (1);
	}
	printf(B_G"   |Enought Arguments \xE2\x9C\x93 \n\n"RESET);
	return (0);
}

int	extension(char *str, char *ext)
{
    int	i;
    int	j;

    i = ft_strlen(str) - 1;
    j = ft_strlen(ext) - 1;
    while (i >= 0 && j >= 0)
    {
        if (str[i] != ext[j])
            return (1);
        i--;
        j--;
    }
    // If we've gone through the entire extension and every character matched,
    // return 0 only if we've also gone through the entire extension.
    // This ensures that the filename isn't something like "file.pngextra".
    return (j < 0) ? 0 : 1;
}

int	first_checks_hub(int ac, char **av, t_core *c)
{
	if (ac_checks(ac))
		error_argument(c);
	if (extension(av[1], ".cub"))
		error_extension(c);
	file_exists(av[1], c);
	c->map->map_path = av[1];
	return (0);
}
