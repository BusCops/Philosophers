/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:33:51 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/28 16:52:03 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->l_fork);
	update_elapsed_time(philo->pg);
	printf("%ld philo %i grab the left fork\n",
		philo->pg->time_stamp, philo->id);
	pthread_mutex_lock(philo->r_fork);
	update_elapsed_time(philo->pg);
	printf("%ld philo %i grab the right fork\n",
		philo->pg->time_stamp, philo->id);
	update_elapsed_time(philo->pg);
	printf("%ld philo %i is eating\n",
		philo->pg->time_stamp, philo->id);
	usleep(100000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_mp	pg;
	t_philo	*philos;
	int		i;

	arg_checker(ac, av);
	initialise_program(&pg, av, &philos);
	pg.forks = creat_forks(&pg);
	philos = creat_philosophers(&pg);
	i = 0;
	while (i < pg.philo_n)
	{
		pthread_join(philos[i].p_th, NULL);
		i++;
	}
	free_all(philos, &pg);
	return (0);
}
