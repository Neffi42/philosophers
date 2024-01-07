/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/07 16:00:35 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(unsigned int *data, const char *av)
{
	char	*tmp;

	*data = ft_atoui(av);
	tmp = ft_uitoa(*data);
	if (!tmp)
		return (error(MEMORY));
	if (ft_strncmp(av, tmp, ft_strlen((char *)av) + 1))
		return (free(tmp), error(OVERFLOW));
	return (free(tmp), EXIT_SUCCESS);
}

int	main(int ac, const char **av)
{
	t_philo	philo;

	if (ac < 5 || ac > 6)
		return (error(USAGE));
	if (check_args(&(philo.nb), av[1]) || check_args(&(philo.die), av[2]) || \
	check_args(&(philo.eat), av[3]) || check_args(&(philo.sleep), av[4]))
		return (EXIT_FAILURE);
	if (ac == 5)
		philo.eat_times = 0;
	else if (check_args(&(philo.eat_times), av[5]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
