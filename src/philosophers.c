/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:41:17 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/06 13:37:41 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	main(int argc, char **argv)
{
	t_rules			rules;
	int				i;

	if (argc < 5 || argc > 6)
		ft_end_process(ERROR_INPUT);
	i = 1;
	while (i < argc)
	{
		if (!(ft_isnumeric(argv[i])))
			ft_end_process(ERROR_INPUT);
		i++;
	}
	ft_init_rules(argv, &rules);
	ft_init_philosophers(&rules);
	ft_init_mutex(&rules);
	if (ft_create_philosopher(&rules))
		ft_end_process(ERROR_THREAD);
	return (0);
}
