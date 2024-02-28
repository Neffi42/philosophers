/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:57:35 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 22:25:34 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_arg(int *data, const char *av, int convert)
{
	char	*tmp;

	*data = ft_atoi(av);
	if (!*data)
		return (error(ARG, (char *)av));
	tmp = ft_itoa(*data);
	if (!tmp)
		return (error(FCT, "ft_uitoa"));
	if (ft_strncmp(av, tmp, ft_strlen((char *)av) + 1))
		return (free(tmp), error(ARG, (char *)av));
	if (*data <= 0)
		return (free(tmp), error(ARG, (char *)av));
	if (convert)
		*data *= 1000;
	return (free(tmp), 0);
}

int	check_rules(int ac, const char **av, t_rules *rules)
{
	if (ac < 5 || ac > 6)
		return (error(USE, NULL));
	if (check_arg(&rules->total_nb, av[1], 0)
		|| check_arg(&rules->time_die, av[2], 1)
		|| check_arg(&rules->time_eat, av[3], 1)
		|| check_arg(&rules->time_sleep, av[4], 1))
		return (1);
	if (ac == 5)
		rules->total_meals = 0;
	else if (check_arg(&rules->total_meals, av[5], 0))
		return (1);
	if (rules->total_nb > 300)
		return (error(NBR, (char *)av[1]));
	return (0);
}
