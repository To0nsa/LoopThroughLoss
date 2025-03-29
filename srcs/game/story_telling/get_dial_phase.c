/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dial_phase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:46:07 by nlouis            #+#    #+#             */
/*   Updated: 2025/03/29 23:34:51 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoopThroughLoss.h"

t_dial_phase	get_mother_dial_phase(t_story *story)
{
	if (story->state == DENIAL_LOOP)
	{
		if (story->loop_number == FIRST_LOOP)
			return (PHASE_0);
		else
			return (PHASE_1);
	}
	else if (story->state == ANGER_LOOP)
		return (PHASE_2);
	return (PHASE_0);
}
	
