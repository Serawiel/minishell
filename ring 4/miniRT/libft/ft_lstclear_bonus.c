/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:36:03 by scavalli          #+#    #+#             */
/*   Updated: 2025/03/04 19:45:56 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*copy;

	if (!*lst || !del || !lst)
		return ;
	while (*lst)
	{
		copy = *lst;
		*lst = (*lst)->next;
		(*del)(copy->content);
		free(copy);
	}
}
