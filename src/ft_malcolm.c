/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:12:05 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/29 03:32:37 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_malcolm.h"

int	main(int ac, char **av)
{
	t_malcolm	malcolm;

	// if (check_uid() != VALID)
	// 	return (EXIT_FAILURE);
	
	if (ac < 5)
		return (print_usage(av[0], EXIT_FAILURE));

	ft_memset(&malcolm, 0, sizeof(malcolm));
	if (parse_args(&malcolm, ac, av) == NON_VALID)
		return (EXIT_FAILURE);

	printf("verbose: %d | gratuitous: %d | timeout: %d\n", malcolm.options.verbose, malcolm.options.gratuitous, malcolm.options.timeout);
}
