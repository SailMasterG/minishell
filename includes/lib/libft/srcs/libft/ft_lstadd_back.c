/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:00:11 by chguerre          #+#    #+#             */
/*   Updated: 2025/12/11 17:27:22 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (!new)
		return ;
	if (*lst == NULL)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	temp = new;
}
