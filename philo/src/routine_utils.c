/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:22:08 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/22 17:23:12 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*find_message(t_state state)
{
	if (state == EATING)
		return ("has taken a fork");
	else if (state == SLEEPING)
		return ("is eating");
	else if (state == THINKING)
		return ("is sleeping");
	else if (state == HAS_FORK)
		return ("is thinking");
	else
		return ("died");
}

t_state find_new_state(t_state state)
{
	if (state == EATING)
		return (SLEEPING);
	else if (state == SLEEPING)
		return (THINKING);
	else if (state == THINKING)
		return (HAS_FORK);
	else if (state == HAS_FORK)
		return (EATING);
	else
		return (DYING);
}
