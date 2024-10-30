/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:48:56 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/30 06:15:15 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

int	spoof_run(t_malcolm *malcolm)
{
	if (fetch_interface(malcolm) == NON_VALID)
		return (print_args_error("%sft_malcolm:%s no matching interface found\n", RED, NC));
	return (VALID);
}
