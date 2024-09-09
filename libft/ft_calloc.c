/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppitzini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:33:09 by pirulenc          #+#    #+#             */
/*   Updated: 2024/09/09 17:26:10 by ppitzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if ((long long)nmemb < 0 || (long long)size < 0)
		return (0);
	ptr = malloc(nmemb * size);
	if (!(ptr))
		return (0);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
