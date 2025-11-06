/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:58:28 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/05 18:09:43 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ANIMATION_H
# define ANIMATION_H

#define ANIM_DEFAULT_PROMPT "\r\033[5C" STYLE BG_WHITE AND BOLD START " minishell " END " % "
#define ANIM_OVERWRITE_NORMAL "\033[s\033[1A" " %3d  minishell  %% \033[u"
#define ANIM_OVERWRITE_SIGNAL "\033[s\r" " %3d  minishell  %% \033[u\n"

# endif
