/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:33:51 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/29 15:52:41 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->l_fork);
	update_elapsed_time(philo->pg);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	update_elapsed_time(philo->pg);
	print_action(philo, "has taken a fork");
	update_elapsed_time(philo->pg);
	print_action(philo, "is eating");
	usleep(100000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_mp	pg;
	t_philo	*philos;
	pthread_t	moni;
	int		i;

	arg_checker(ac, av);
	initialise_program(&pg, av, &philos);
	creat_forks(&pg);
	philos = creat_philosophers(&pg);
	if (pthread_create(&moni, NULL, monitor, philos) != 0)
		error_handle("creating thread fail", &pg, philos);
	i = 0;
	while (i < pg.philo_n)
	{
		pthread_join(philos[i].p_th, NULL);
		i++;
	}
	free_all(philos, &pg);
	return (0);
}
