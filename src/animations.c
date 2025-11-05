/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:01:33 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/05 18:24:43 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *frame_train(unsigned int frame)
{
	const char	*frames[20] = {
		STYLE BG_CUSTOM "196" AND BOLD START " minishel🚂" END, 
		STYLE BG_CUSTOM "197" AND BOLD START " minishe🚂 " END, 
		STYLE BG_CUSTOM "198" AND BOLD START " minish🚂l " END, 
		STYLE BG_CUSTOM "199" AND BOLD START " minis🚂ll " END, 
		STYLE BG_CUSTOM "200" AND BOLD START " mini🚂ell " END, 
		STYLE BG_CUSTOM "201" AND BOLD START " min🚂hell " END, 
		STYLE BG_CUSTOM "207" AND BOLD START " mi🚂shell " END, 
		STYLE BG_CUSTOM "213" AND BOLD START " m🚂ishell " END, 
		STYLE BG_CUSTOM "219" AND BOLD START " 🚂nishell " END, 
		STYLE BG_CUSTOM "225" AND BOLD START "🚂inishell " END,
		STYLE BG_CUSTOM "231" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "230" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "229" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "228" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "227" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "226" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "220" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "214" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "208" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "202" AND BOLD START " minishell " END
	};

	return (frames[frame]);
}

const char *frame_fish(unsigned int frame)
{
	const char	*frames[20] = {
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishel🐠" END, 
		STYLE BG_BLUE AND BOLD START " minishe🐠 " END, 
		STYLE BG_BLUE AND BOLD START " minish🐠l " END, 
		STYLE BG_BLUE AND BOLD START " minis🐠ll " END, 
		STYLE BG_BLUE AND BOLD START " min🐠hell " END, 
		STYLE BG_BLUE AND BOLD START " mi🐠shell " END, 
		STYLE BG_BLUE AND BOLD START " m🐠ishell " END, 
		STYLE BG_BLUE AND BOLD START " 🐠nishell " END, 
		STYLE BG_BLUE AND BOLD START "🐠inishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END, 
		STYLE BG_BLUE AND BOLD START " minishell " END,
		STYLE BG_BLUE AND BOLD START " minishell " END, 
	};

	return (frames[frame]);
}

