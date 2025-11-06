/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:51:39 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/06 15:30:29 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	busy_wait(int iterations, int divider)
{
	int				counter;
	unsigned int	work;

	counter = 0;
	work = 50;
	if (divider == 0)
		divider = 3;
	while (counter < iterations)
	{
		work *= work;
		work /= divider;
		counter++;
	}
	return ;
}

const char	*animation_switch(int t)
{
	if (data()->animation_variant == 0)
		return (frame_train(t));
	else if (data()->animation_variant == 1)
		return (frame_sparkle(t));
	else if (data()->animation_variant == 2)
		return (frame_train_2(t));
	else if (data()->animation_variant == 3)
		return (frame_bowling(t));
	else if (data()->animation_variant == 4)
		return (frame_upercase(t));
	else if (data()->animation_variant == 5)
		return (frame_moving_tile(t));
	else if (data()->animation_variant == 6)
		return (frame_smallcase(t));
	else
		return (frame_fish(t));
}
