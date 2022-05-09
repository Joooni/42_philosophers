/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:52:59 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/09 13:23:54 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

static void	ft_one_philo(t_rules *rules);

void	*entry(void *void_ptr_philo)
{
	t_philosopher	*philosopher;
	t_rules			*rules;

	philosopher = (t_philosopher *)void_ptr_philo;
	rules = philosopher->rules;
	if (rules->nbr_philosophers > 1)
	{
		if (philosopher->id % 2)
			usleep((rules->time_to_sleep) + 50);
		while (ft_read_dead(rules))
		{
			ft_philo_meal(rules, philosopher);
			pthread_mutex_lock(&(rules->food_check));
			if (rules->full_bellies)
			{
				pthread_mutex_unlock(&(rules->food_check));
				break ;
			}
			pthread_mutex_unlock(&(rules->food_check));
			ft_print_philo(rules, philosopher->id, "is sleeping");
			ft_sleep(rules->time_to_sleep, rules);
			ft_print_philo(rules, philosopher->id, "is thinking");
		}
	}
	return (NULL);
}

// Create a new thread for each philosopher with the routine defined in entry
int	ft_create_philosopher(t_rules *rules)
{
	int				i;
	t_philosopher	*philo;

	philo = rules->philosophers;
	i = 0;
	rules->start_time = ft_time();
	if (rules->nbr_philosophers == 1)
	{
		ft_one_philo(rules);
		return (0);
	}
	while (i < rules->nbr_philosophers)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, entry, &(philo[i])))
			ft_end_process(ERROR_THREAD);
		pthread_mutex_lock(&(rules->mealtime_check));
		philo[i].time_last_meal = ft_time();
		pthread_mutex_unlock(&(rules->mealtime_check));
		i++;
	}
	ft_death_monitor(rules, rules->philosophers);
	ft_end_threads(rules);
	ft_end_mutex(rules);
	return (0);
}

static void	ft_one_philo(t_rules *rules)
{
	if (pthread_create(&(rules->philosophers[0].thread_id),
			NULL, entry, &(rules->philosophers[0])))
		ft_end_process(ERROR_THREAD);
	ft_print_philo(rules, 0, "had taken a fork");
	ft_sleep(rules->time_to_die, rules);
	ft_print_philo(rules, 0, "has dies");
	ft_end_threads(rules);
	ft_end_mutex(rules);
}

void	ft_end_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbr_philosophers)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->mealtime_check));
	pthread_mutex_destroy(&(rules->food_check));
	pthread_mutex_destroy(&(rules->pulse_check));
	free(rules->forks);
}

void	ft_end_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbr_philosophers)
	{
		pthread_join(rules->philosophers[i].thread_id, NULL);
		i++;
	}
	free(rules->philosophers);
}
