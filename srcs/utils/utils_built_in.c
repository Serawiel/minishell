/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:57:03 by cprot             #+#    #+#             */
/*   Updated: 2025/09/13 10:03:29 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

t_localvar	*is_local(t_localvar *local, char *name)
{
	if (!local)
		return (NULL);
	while (local)
	{
		if (ft_strcmp(local->name, name) == 0)
			return (local);
		local = local->next;
	}
	return (NULL);
}
