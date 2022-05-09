/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:49:56 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/05 16:29:36 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_full_bellies_check(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(rules->food_check));
	while (rules->nbr_of_req_meals != -1 && i < rules->nbr_philosophers \
		&& rules->philosophers[i].nbr_of_meals >= rules->nbr_of_req_meals)
			i++;
	if (i == rules->nbr_philosophers)
		rules->full_bellies = 1;
	pthread_mutex_unlock(&(rules->food_check));
}

int	ft_read_dead(t_rules *rules)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&(rules->pulse_check));
	if (rules->dead_philosopher == 1)
		ret = 0;
	pthread_mutex_unlock(&(rules->pulse_check));
	return (ret);
}
