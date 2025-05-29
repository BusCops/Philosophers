/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_everything.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:03:42 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/29 15:50:42 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialise_program(t_mp *pg, char **av, t_philo **philos)
{
	pg->forks = NULL;
	*philos = NULL;
	pthread_mutex_init(&pg->dl, NULL);
	pg->is_dead = 0;
	pg->start_time = get_time();
	pg->philo_n = bc_atoi(av[1]);
	pg->t_die = bc_atoi(av[2]);
	pg->t_eat = bc_atoi(av[3]);
	pg->t_sleep = bc_atoi(av[4]);
	if (!av[5] || !bc_strlen(av[5]))
		pg->n_t_eat = 0;
	else
		pg->n_t_eat = bc_atoi(av[5]);
	if (!pg->philo_n)
		print_args_error("philosopher number can't be zero");
	if (pg->philo_n == 1)
		pg->job = single_philo;
	else if (pg->philo_n % 2 == 0)
		pg->job = even_philo;
	else
		pg->job = routine;
}

t_philo	*creat_philosophers(t_mp *pg)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * pg->philo_n);
	if (!philos)
		error_handle("allocation fail", pg, philos);
	while (i < pg->philo_n)
	{
		philos[i].id = i;
		philos[i].pg = pg;
		philos[i].n_eat = 0;
		philos[i].last_meal = 0;
		if (i == 0)
			philos[i].l_fork = pg->forks[pg->philo_n - 1];
		else
			philos[i].l_fork = pg->forks[i - 1];
		philos[i].r_fork = pg->forks[i];
		if (pthread_create(&philos[i].p_th, NULL, pg->job, &philos[i]) != 0)
			error_handle("creating thread fail", pg, philos);
		i++;
	}
	return (philos);
}

void	creat_forks(t_mp *pg)
{
	pthread_mutex_t	**forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * pg->philo_n);
	if (!forks)
		error_handle("allocation fail", pg, NULL);
	pg->forks = forks;
	initialize_pointers((void ***)&forks, pg->philo_n);
	while (i < pg->philo_n)
	{
		forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			error_handle("allocation fail", pg, NULL);
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
}
