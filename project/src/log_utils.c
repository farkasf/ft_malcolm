/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 03:06:43 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/31 03:07:40 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

void	print_timeout(int iter, int timeout)
{
	int	interval;

	if (timeout < 3)
		interval = timeout * 3;
	else
		interval = timeout;
	if (iter % interval != 0)
		return ;
	dprintf(STDOUT_FILENO, "%s%sTIMEOUT:%s no packets received (%d iters) [%s]\n", PAD, BL, NC, iter, fetch_time());
}
