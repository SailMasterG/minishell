/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 18:45:41 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 18:45:41 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		count;

	count = 0;
	current = cmd;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}