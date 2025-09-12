/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_styles.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:09:00 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/11 19:08:32 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STYLES_H
# define LIBFT_STYLES_H

/* --- colors -------------------------------------------------------------- */

# define BLACK "30"
# define RED "31"
# define GREEN "32"
# define YELLOW "33"
# define BLUE "34"
# define MAGENTA "35"
# define CYAN "36"
# define WHITE "37"
# define BRIGHT_RED "91"
# define BRIGHT_GREEN "92"
# define BRIGHT_YELLOW "93"
# define BRIGHT_BLUE "94"
# define BRIGHT_MAGENTA "95"
# define BRIGHT_CYAN "96"
# define BRIGHT_WHITE "97"

/* --- background colors ---------------------------------------------------- */

# define BG_BLACK "40"
# define BG_RED "41"
# define BG_GREEN "42"
# define BG_YELLOW "43"
# define BG_BLUE "44"
# define BG_AGENTA "45"
# define BG_CYAN "46"
# define BG_WHITE "47"
# define BG_BRIGHT_RED "101"
# define BG_BRIGHT_GREEN "102"
# define BG_BRIGHT_YELLOW "103"
# define BG_BRIGHT_BLUE "104"
# define BG_BRIGHT_MAGENTA "105"
# define BG_BRIGHT_CYAN "106"
# define BG_BRIGHT_WHITE "107"

/* --- styles --------------------------------------------------------------- */

# define RESET "0"
# define BOLD "1"
# define DIM "2"
# define ITALIC "3"
# define UNDERLINE "4"
# define BLINK "5"
# define INVERT "7"
# define HIDDEN "8"
# define STRIKETHROUGH "9"

/* --- modular -------------------------------------------------------------- */

# define STYLE "\033["
# define AND ";"
# define START "m"
# define END "\033[0m"
# define ERROR "1;31"
# define SUCCESS "1;92"
# define CLEAR "\033[2J"

#endif
