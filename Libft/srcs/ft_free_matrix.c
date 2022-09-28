/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:08:34 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/26 19:12:11 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_free_matrix(char **matrix)
{
    int i;

    i = 0;
    if (!matrix)
        return ;
    while (matrix[i])
        i++;
    free(matrix);
}