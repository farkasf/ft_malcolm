/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:20:33 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/26 23:34:17 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isxdigit(int c)
{
	if ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (0);
}