/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:47:53 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/09 14:41:49 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int horizontal_resolution(void)
{
	int horizontal_resolution;
	
	horizontal_resolution = ((float)16 / 9) * WIDTH ; //widescreen 16:9
	return (horizontal_resolution);
}