/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/20 17:36:51 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
int main ()
{
    printf ("%d \n", file_format("holala"));
    printf ("%d \n", file_format("holala.rt"));
    printf ("%d \n", file_format(".rt"));
    printf ("%d el vacio\n", file_format(""));
    printf ("%d \n", file_format(".r"));
    printf ("%d \n", file_format("holala.wx"));
    printf ("%d \n", file_format("123456789123456789.rt"));
}