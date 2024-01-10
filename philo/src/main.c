/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/10 18:40:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(unsigned int *data, const char *av)
{
	char	*tmp;

	*data = ft_atoui(av);
	if (!*data)
		return (error(ARGUMENT, (char *)av));
	tmp = ft_uitoa(*data);
	if (!tmp)
		return (error(FUNCTION, "ft_uitoa"));
	if (ft_strncmp(av, tmp, ft_strlen((char *)av) + 1))
		return (free(tmp), error(ARGUMENT, (char *)av));
	return (free(tmp), EXIT_SUCCESS);
}

static int	check_args(int ac, const char **av, t_args *args)
{
	if (ac < 5 || ac > 6)
		return (error(USAGE, NULL));
	if (check_arg(&args->nb, av[1]) || check_arg(&args->die, av[2]) || \
	check_arg(&args->eat, av[3]) || check_arg(&args->sleep, av[4]))
		return (EXIT_FAILURE);
	if (ac == 5)
		args->eat_times = 0;
	else if (check_arg(&args->eat_times, av[5]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int ac, const char **av)
{
	t_args		args;

	if (check_args(ac, av, &args))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
