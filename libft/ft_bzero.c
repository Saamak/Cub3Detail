/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:48:58 by pirulenc          #+#    #+#             */
/*   Updated: 2024/09/09 17:31:51 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			x;
	unsigned char	*stock;

	x = 0;
	stock = (unsigned char *)s;
	while (x < n)
	{
		stock[x] = 0;
		x++;
	}
}
