/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masterg <masterg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:53:20 by masterg           #+#    #+#             */
/*   Updated: 2025/12/03 13:57:09 by masterg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

/*
int main(){
   char caracter;
	caracter = 200;

	ft_isascii(caracter);

	if (ft_isascii(caracter)){
		printf("El caracter: %c pertenece a ascii\n", caracter);
	}else {
		printf("El caracter %c no pertenece a la tabla ascii\n", caracter);
	}

	return (0);
  }*/
