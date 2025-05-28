/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:11:05 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/28 16:03:08 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	update_elapsed_time(philo->pg);
	philo->last_meal = philo->pg->time_stamp;
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a fork");
	while (1)
	{
		update_elapsed_time(philo->pg);
		if ((philo->pg->time_stamp - philo->last_meal) >= philo->pg->t_die)
			break ;
	}
	print_action(philo, "died");
	return (NULL);
}
