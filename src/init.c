/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 08:44:24 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/09 14:24:50 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

// Initialize philosopher struct according to rules
void	ft_init_philosophers(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbr_philosophers)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].nbr_of_meals = 0;
		rules->philosophers[i].id_fork_left = i;
		rules->philosophers[i].id_fork_right = (i + 1)
			% rules->nbr_philosophers;
		rules->philosophers[i].time_last_meal = 0;
		rules->philosophers[i].rules = rules;
		i++;
	}
}

/*
Initialize rules structure with values passed on program call
Malloc space for philosphers inside rules struct
check if input makes sense
-> enough forks for philosophers to feed themselves
-> times bigger than zero
 */
void	ft_init_rules(char **argv, t_rules *rules)
{
	int	i;

	rules->nbr_philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->dead_philosopher = 0;
	rules->full_bellies = 0;
	i = -1;
	rules->philosophers = malloc(sizeof(t_philosopher)
			* rules->nbr_philosophers);
	if (argv[5])
		rules->nbr_of_req_meals = ft_atoi(argv[5]);
	else
		rules->nbr_of_req_meals = -1;
	if (rules->time_to_die < 0 || rules->time_to_eat < 0
		|| rules->time_to_sleep < 0 || rules->nbr_philosophers < 1
		|| (rules->nbr_of_req_meals < 1 && rules->nbr_of_req_meals != -1))
		ft_end_process(ERROR_INPUT);
}

void	ft_init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(
			sizeof(pthread_mutex_t) * rules->nbr_philosophers);
	while (i < rules->nbr_philosophers)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			ft_end_process(ERROR_MUTEX);
		i++;
	}
	if (pthread_mutex_init(&(rules->writing), NULL))
		ft_end_process(ERROR_MUTEX);
	if (pthread_mutex_init(&(rules->mealtime_check), NULL))
		ft_end_process(ERROR_MUTEX);
	if (pthread_mutex_init(&(rules->pulse_check), NULL))
		ft_end_process(ERROR_MUTEX);
	if (pthread_mutex_init(&(rules->food_check), NULL))
		ft_end_process(ERROR_MUTEX);
}
