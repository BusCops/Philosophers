/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:36:03 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/28 16:52:11 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_mp
{
	int				philo_n;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				n_t_eat;
	long			start_time;
	long			time_stamp;
	void			*(*job)(void *);
	pthread_mutex_t	**forks;
}	t_mp;

typedef struct s_philo
{
	pthread_t		p_th;
	int				id;
	long			last_meal;
	// need to add some data i will need to use
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_mp			*pg;
}	t_philo;

//helper function
int				bc_is_digit(int c);
int				bc_atoi(const char *s);
size_t			bc_strlen(const char *string);
int				bc_strcmp(const char *s1, const char *s2);
void			initialize_pointers(void ***ptr, int count);

//program arg check function
void			print_args_error(char *s);
void			arg_checker(int ac, char **av);

//initialize everything
void			initialise_program(t_mp *pg, char **av, t_philo **philos);
t_philo			*creat_philosophers(t_mp *pg);
pthread_mutex_t	**creat_forks(t_mp *pg);

//utils
void			error_handle(const char *s, t_mp *pg, t_philo *philos);
long			get_time(void);
void			update_elapsed_time(t_mp *pg);
void			print_action(t_philo *philo, const char *s);
void			free_all(t_philo *philos, t_mp *pg);

//philosophers job
void			*single_philo(void	*ptr);

//program function
void			*routine(void *philo);

#endif