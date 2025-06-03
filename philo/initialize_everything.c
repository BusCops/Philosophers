/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_everything.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:03:42 by abenzaho          #+#    #+#             */
/*   Updated: 2025/06/03 14:22:57 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialise_program(t_mp *pg, char **av, t_philo **philos)
{
	pg->forks = NULL;
	pg->meals = NULL;
	*philos = NULL;
	pg->is_dead = 0;
	pg->start_time = get_time() + 300;
	pg->philo_n = bc_atoi(av[1]);
	pg->t_die = bc_atoi(av[2]);
	pg->t_eat = bc_atoi(av[3]);
	pg->t_sleep = bc_atoi(av[4]);
	if (pg->philo_n > 200)
		return (print_args_error("number of philosopher can't "
				"be more than 200"), 1);
	if (!av[5] || !bc_strlen(av[5]))
		pg->n_t_eat = 0;
	else if (!bc_atoi(av[5]))
		return (print_args_error("number of time to eat can't be zero"), 1);
	else
		pg->n_t_eat = bc_atoi(av[5]);
	if (!pg->philo_n)
		return (print_args_error("philosopher number can't be zero"), 1);
	if (pg->philo_n == 1)
		pg->job = single_philo;
	else
		pg->job = even_philo;
	return (0);
}

t_philo	*creat_philosophers(t_mp *pg)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * pg->philo_n);
	if (!philos)
		return (error_handle("allocation fail", pg, philos), NULL);
	while (i < pg->philo_n)
	{
		philos[i].id = i + 1;
		philos[i].pg = pg;
		philos[i].n_eat = 0;
		philos[i].last_meal = 0;
		philos[i].meals_n = pg->meals[i];
		if (i == 0)
			philos[i].l_fork = pg->forks[pg->philo_n - 1];
		else
			philos[i].l_fork = pg->forks[i - 1];
		philos[i].r_fork = pg->forks[i];
		if (pthread_create(&philos[i].p_th, NULL, pg->job, &philos[i]) != 0)
			return (error_handle("creating thread fail", pg, philos), NULL);
		i++;
	}
	return (philos);
}

int	creat_forks(t_mp *pg)
{
	pthread_mutex_t	**forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * pg->philo_n);
	if (!forks)
		return (error_handle("allocation fail", pg, NULL), 1);
	pg->forks = forks;
	initialize_pointers((void ***)&forks, pg->philo_n);
	while (i < pg->philo_n)
	{
		forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (error_handle("allocation fail", pg, NULL), 1);
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (0);
}

int	creat_meals(t_mp *pg)
{
	pthread_mutex_t	**meals;
	int				i;

	i = 0;
	meals = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * pg->philo_n);
	if (!meals)
		return (error_handle("allocation fail", pg, NULL), 1);
	pg->meals = meals;
	initialize_pointers((void ***)&meals, pg->philo_n);
	while (i < pg->philo_n)
	{
		meals[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!meals[i])
			return (error_handle("allocation fail", pg, NULL), 1);
		pthread_mutex_init(meals[i], NULL);
		i++;
	}
	return (0);
}
