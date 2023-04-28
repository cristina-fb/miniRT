/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fT_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:02:31 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 16:03:52 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}
