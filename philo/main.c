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

void	error_handle(const char *s, t_mp *pg, t_philo *philos)
{
	write(2, "philo : ", 8);
	write(2, s, bc_strlen(s));
	write(2, "\n", 1);
	free_all(philos, pg);
}

void	join_threads(t_mp *pg, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < pg->philo_n)
	{
		pthread_join(philos[i].p_th, NULL);
		i++;
	}
}

void	destory_mutex(t_mp *pg)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&pg->dl);
	pthread_mutex_destroy(&pg->time);
	pthread_mutex_destroy(&pg->print);
	while (i < pg->philo_n)
	{
		pthread_mutex_destroy(pg->meals[i]);
		pthread_mutex_destroy(pg->forks[i]);
		i++;
	}
}

void	creat_mutex(t_mp *pg)
{
	pthread_mutex_init(&pg->dl, NULL);
	pthread_mutex_init(&pg->time, NULL);
	pthread_mutex_init(&pg->print, NULL);
}

int	main(int ac, char **av)
{
	t_mp		pg;
	t_philo		*philos;
	pthread_t	moni;

	if (arg_checker(ac, av))
		return (1);
	if (initialise_program(&pg, av, &philos))
		return (1);
	if (creat_forks(&pg) || creat_meals(&pg))
		return (1);
	creat_mutex(&pg);
	philos = creat_philosophers(&pg);
	if (!philos)
		return (1);
	if (pthread_create(&moni, NULL, monitor, philos) != 0)
		return (error_handle("creating thread fail", &pg, philos), 1);
	pthread_join(moni, NULL);
	join_threads(&pg, philos);
	destory_mutex(&pg);
	free_all(philos, &pg);
	return (0);
}
