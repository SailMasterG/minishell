/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:00:22 by chguerre          #+#    #+#             */
/*   Updated: 2025/12/13 02:01:42 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*temp;
	void	*content;

	newlist = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		temp = ft_lstnew(content);
		if (!temp)
		{
			del(content);
			ft_lstclear(&newlist, del);
			free(newlist);
			return (NULL);
		}
		ft_lstadd_back(&newlist, temp);
		lst = lst->next;
	}
	return (newlist);
}
