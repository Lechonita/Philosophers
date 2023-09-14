/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:32:00 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/14 19:34:33 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
		((unsigned char *)s)[n] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb != 0 && size > ((SIZE_MAX) - 1) / nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
