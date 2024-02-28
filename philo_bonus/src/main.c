/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 22:26:26 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static int	run(t_philo *philos, t_rules *rules, t_vars *vars)
// {
// 	set_var(&vars->run, 1);
// 	while (get_var(&vars->run))
// 	{
// 		usleep(1000);
// 		if (rules->total_meals && get_var(&vars->meals) >= rules->total_nb)
// 		{
// 			set_var(&vars->run, 0);
// 			break ;
// 		}
// 	}
// 	return (destroy(philos, rules->total_nb), 0);
// }

int	main(int ac, const char **av)
{
	// t_philo		*philos;
	// t_rules		rules;
	// t_vars		vars;

	// if (check_rules(ac, av, &rules))
	// 	return (1);
	// philos = ft_calloc(rules.total_nb, sizeof(t_philo));
	// if (!philos)
	// 	return (1);
	// if (init_vars(&vars))
	// 	return (free(philos), 1);
	// if (init_philos(philos, &vars, &rules))
	// 	return (1);
	// return (run(philos, &rules, &vars));
}
