/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:58:28 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/07 15:35:29 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# define ANIM_DEFAULT_PROMPT "\033[5C\033[47;1m minishell \033[0m % "
# define ANIM_OVERWRITE_NORMAL "\033[s\033[1A %3d  minishell  %% \033[u"
# define ANIM_OVERWRITE_SIGNAL "\033[s\r %3d  minishell  %% \033[u\n"

# define SMALL_FRONT "\033[104;1m"
# define SMALL_MITLE ""

# define M_TILE_FRONT "\033[104;1m"
# define M_TILE_MTITLE "\033[103;1m"

void		animation_end(int sig);
void		animation_init(void);
void		animation_kill(void);
void		animation(void);
void		busy_wait(int iterations, int divider);
const char	*animation_switch(int t);

const char	*frame_train(unsigned int frame);
const char	*frame_fish(unsigned int frame);
const char	*frame_sparkle(unsigned int frame);
const char	*frame_train_2(unsigned int frame);
const char	*frame_emote(unsigned int frame);

const char	*frame_upercase(unsigned int frame);
const char	*frame_moving_tile(unsigned int frame);
const char	*frame_smallcase(unsigned int frame);
const char	*frame_bowling(unsigned int frame);

#endif
