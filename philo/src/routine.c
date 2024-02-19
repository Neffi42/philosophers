/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/19 23:53:59 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo, t_args args)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"));
	printf("%ld: %u is waiting\n", tv.tv_usec, philo->nb);
	while (1)
	{
	// 	if (change_state(&tv, philo, EATING))
	// 		return (EXIT_FAILURE);
	// 	usleep(args.eat * 1000);
	// 	if (change_state(&tv, philo, SLEEPING))
	// 		return (EXIT_FAILURE);
	// 	usleep(args.sleep * 1000);
	// 	if (change_state(&tv, philo, THINKING))
	// 		return (EXIT_FAILURE);
	}
	return (NULL);
}
