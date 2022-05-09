/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:15:10 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/09 09:06:39 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_print_philo(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->writing));
	if (ft_read_dead(rules))
		printf("%lli %d %s\n", ft_time() - rules->start_time, id + 1, string);
	pthread_mutex_unlock(&(rules->writing));
}

void	ft_philo_meal(t_rules *rules, t_philosopher *philosopher)
{
	pthread_mutex_lock(&(rules->forks[philosopher->id_fork_left]));
	ft_print_philo(rules, philosopher->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philosopher->id_fork_right]));
	ft_print_philo(rules, philosopher->id, "has taken a fork");
	pthread_mutex_lock(&(rules->mealtime_check));
	philosopher->time_last_meal = ft_time();
	pthread_mutex_unlock(&(rules->mealtime_check));
	ft_print_philo(rules, philosopher->id, "is eating");
	ft_sleep(rules->time_to_eat, rules);
	pthread_mutex_unlock(&(rules->forks[philosopher->id_fork_left]));
	pthread_mutex_unlock(&(rules->forks[philosopher->id_fork_right]));
	pthread_mutex_lock(&(rules->food_check));
	philosopher->nbr_of_meals++;
	pthread_mutex_unlock(&(rules->food_check));
}

void	ft_death_monitor(t_rules *rules, t_philosopher *philo)
{
	int	i;

	while (!rules->full_bellies)
	{
		i = -1;
		while (i++ < rules->nbr_philosophers && ft_read_dead(rules))
		{
			pthread_mutex_lock(&(rules->mealtime_check));
			if ((ft_time() - philo->time_last_meal) > rules->time_to_die)
			{
				ft_print_philo(rules, philo->id, "has died");
				pthread_mutex_lock(&(rules->pulse_check));
				rules->dead_philosopher = 1;
				pthread_mutex_unlock(&(rules->pulse_check));
			}
			pthread_mutex_unlock(&(rules->mealtime_check));
			usleep(50);
		}
		if (rules->dead_philosopher)
			break ;
		ft_full_bellies_check(rules);
	}
}

void	ft_sleep(long long time, t_rules *rules)
{
	long long	i;

	i = ft_time();
	while ((ft_read_dead(rules)))
	{
		if ((ft_time() - i) >= time)
			break ;
		usleep(50);
	}
}
