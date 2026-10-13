/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguer <chguerre@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:40:49 by chguer            #+#    #+#             */
/*   Updated: 2025/12/06 21:40:58 by chguer           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t counter, size_t taille)
{
	void	*ptr;
	size_t	taille_total;

	taille_total = counter * taille;
	ptr = malloc(taille_total);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, taille_total);
	return (ptr);
}
