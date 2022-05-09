/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:47:40 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/06 13:40:18 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define ERROR_INPUT	"Error - Wrong Input"
# define ERROR_THREAD	"Error - Thread generation failed"
# define ERROR_MUTEX	"Error - Mutex initialization failed"

struct	s_philosopher;
/* 
Rule structure
@param nbr_philosophers		number of philosophers and forks
@param time_to_die			time for philosopher to die
@param time_to_eat			time it takes philosopher to eat
@param time_to_sleep			time philosopher sleeps after eating
@param nbr_of_req_meals		optional: nbr each philosopher needs to eat 
							for sim to finish (-1: no input)
@param start_time			time at start
@param dead_philo			flag to check if a philosopher died
@param full_bellies			flag to see if every philosopher has eaten nbr of req meals
@param philosophers			array of philosophers
@param pulse_check			mutex lock to check if philosopher died 
@param forks					mutex lock for forks that are currently in use
@param writing				mutex lock for writing so that messages don't get mixed up
@param food_check			mutex lock to check nbr of consumed meals
@param mealtime_check		mutex lock to see and change last consumed meal
 */
typedef struct s_rules
{
	int						nbr_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nbr_of_req_meals;
	long long				start_time;
	int						full_bellies;
	int						dead_philosopher;
	struct s_philosopher	*philosophers;
	pthread_mutex_t			pulse_check;
	pthread_mutex_t			*forks;
	pthread_mutex_t			writing;
	pthread_mutex_t			food_check;
	pthread_mutex_t			mealtime_check;
}	t_rules;

/* 
@param id	ID of current philosopher
@param nbr_of_meals	nbr of meals already consumed
@param id_fork_left	index of left fork (n+1 % nbr_philosophers)
@param id_fork_right	index of right fork (n)
@param time_last_meal	time since last meal
@param rules			struct with rules
@param thread_id	ID of assigned phtread
 */
typedef struct s_philosopher
{
	int				id;
	int				nbr_of_meals;
	int				id_fork_left;
	int				id_fork_right;
	long			time_last_meal;
	struct s_rules	*rules;
	pthread_t		thread_id;
}	t_philosopher;

// thread creation and initialization

int			ft_create_philosopher(t_rules *rules);
void		ft_init_rules(char **argv, t_rules *rules);
void		ft_init_philosophers(t_rules *rules);
void		ft_init_mutex(t_rules *rules);

// utility functions

void		ft_end_process(char *s);
int			ft_atoi(const char *str);
long long	ft_time(void);
int			ft_isnumeric(char *str);

// utility functions specific to philosophers

void		ft_print_philo(t_rules *rules, int id, char *string);
void		ft_philo_meal(t_rules *rules, t_philosopher *philosopher);
void		ft_death_monitor(t_rules *rules, t_philosopher *philo);
void		ft_sleep(long long time, t_rules *rules);
void		ft_end_threads(t_rules *rules);
void		ft_end_mutex(t_rules *rules);
int			ft_read_dead(t_rules *rules);
void		ft_full_bellies_check(t_rules *rules);

// threading functions
void		*entry(void *void_ptr_philo);
int			ft_create_philosopher(t_rules *rules);
#endif