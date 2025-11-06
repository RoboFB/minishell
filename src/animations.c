/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:01:33 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/06 12:36:31 by rgohrig          ###   ########.fr       */
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


const char *frame_upercase(unsigned int frame)
{
	const char	*frames[20] = {
		STYLE BG_BRIGHT_MAGENTA START " Minishell " END, 
		STYLE BG_BRIGHT_MAGENTA START " mInishell " END, 
		STYLE BG_BRIGHT_MAGENTA START " miNishell " END, 
		STYLE BG_BRIGHT_MAGENTA START " minIshell " END, 
		STYLE BG_BRIGHT_MAGENTA START " miniShell " END, 
		STYLE BG_BRIGHT_MAGENTA START " minisHell " END, 
		STYLE BG_BRIGHT_MAGENTA START " minishEll " END, 
		STYLE BG_BRIGHT_MAGENTA START " minisheLl " END, 
		STYLE BG_BRIGHT_MAGENTA START " minishelL " END, 
		STYLE BG_BRIGHT_MAGENTA START " minishelL " END, 
		STYLE BG_BRIGHT_MAGENTA START " minisheLl " END, 
		STYLE BG_BRIGHT_MAGENTA START " minishEll " END, 
		STYLE BG_BRIGHT_MAGENTA START " minisHell " END, 
		STYLE BG_BRIGHT_MAGENTA START " miniShell " END, 
		STYLE BG_BRIGHT_MAGENTA START " minIshell " END, 
		STYLE BG_BRIGHT_MAGENTA START " miNishell " END, 
		STYLE BG_BRIGHT_MAGENTA START " mInishell " END, 
		STYLE BG_BRIGHT_MAGENTA START " Minishell " END, 
		STYLE BG_BRIGHT_MAGENTA START " Minishell " END, 
		STYLE BG_BRIGHT_MAGENTA START " Minishell " END, 
	};

	return (frames[frame]);
}

# define FRONT "\033[104;1m"
# define MTITLE "\033[103;1m"

const char *frame_moving_tile(unsigned int frame)
{
	const char	*frames[20] = {
		FRONT "" MTITLE " " FRONT "minishell " END, 
		FRONT " " MTITLE "m" FRONT "inishell " END, 
		FRONT " m" MTITLE "i" FRONT "nishell " END, 
		FRONT " mi" MTITLE "n" FRONT "ishell " END, 
		FRONT " min" MTITLE "i" FRONT "shell " END, 
		FRONT " mini" MTITLE "s" FRONT "hell " END, 
		FRONT " minis" MTITLE "h" FRONT "ell " END, 
		FRONT " minish" MTITLE "e" FRONT "ll " END, 
		FRONT " minishe" MTITLE "l" FRONT "l " END, 
		FRONT " minishel" MTITLE "l" FRONT " " END, 
		FRONT " minishell" MTITLE " " FRONT "" END, 
		FRONT " minishel" MTITLE "l" FRONT " " END, 
		FRONT " minishe" MTITLE "l" FRONT "l " END, 
		FRONT " minish" MTITLE "e" FRONT "ll " END, 
		FRONT " minis" MTITLE "h" FRONT "ell " END, 
		FRONT " mini" MTITLE "s" FRONT "hell " END, 
		FRONT " min" MTITLE "i" FRONT "shell " END, 
		FRONT " mi" MTITLE "n" FRONT "ishell " END, 
		FRONT " m" MTITLE "i" FRONT "nishell " END, 
		FRONT " " MTITLE "m" FRONT "inishell " END, 
	};

	return (frames[frame]);
}

# define FRONT_2 "\033[104;1m"
# define MTITLE_2 ""

const char *frame_smallcase(unsigned int frame)
{
	const char	*frames[20] = {
		FRONT_2 "" MTITLE_2 " " FRONT_2 "ᵐⁱⁿⁱˢʰᵉˡˡ " END, 
		FRONT_2 " " MTITLE_2 "ᵐ" FRONT_2 "ⁱⁿⁱˢʰᵉˡˡ " END, 
		FRONT_2 " m" MTITLE_2 "ⁱ" FRONT_2 "ⁿⁱˢʰᵉˡˡ " END, 
		FRONT_2 " mi" MTITLE_2 "ⁿ" FRONT_2 "ⁱˢʰᵉˡˡ " END, 
		FRONT_2 " min" MTITLE_2 "ⁱ" FRONT_2 "ˢʰᵉˡˡ " END, 
		FRONT_2 " mini" MTITLE_2 "ˢ" FRONT_2 "ʰᵉˡˡ " END, 
		FRONT_2 " minis" MTITLE_2 "ʰ" FRONT_2 "ᵉˡˡ " END, 
		FRONT_2 " minish" MTITLE_2 "ᵉ" FRONT_2 "ˡˡ " END, 
		FRONT_2 " minishe" MTITLE_2 "ˡ" FRONT_2 "ˡ " END, 
		FRONT_2 " minishel" MTITLE_2 "ˡ" FRONT_2 " " END, 
		FRONT_2 " minishell" MTITLE_2 " " FRONT_2 "" END, 
		FRONT_2 " minishel" MTITLE_2 "ˡ" FRONT_2 " " END, 
		FRONT_2 " minishe" MTITLE_2 "ˡ" FRONT_2 "ˡ " END, 
		FRONT_2 " minish" MTITLE_2 "ᵉ" FRONT_2 "ˡˡ " END, 
		FRONT_2 " minis" MTITLE_2 "ʰ" FRONT_2 "ᵉˡˡ " END, 
		FRONT_2 " mini" MTITLE_2 "ˢ" FRONT_2 "ʰᵉˡˡ " END, 
		FRONT_2 " min" MTITLE_2 "ⁱ" FRONT_2 "ˢʰᵉˡˡ " END, 
		FRONT_2 " mi" MTITLE_2 "ⁿ" FRONT_2 "ⁱˢʰᵉˡˡ " END, 
		FRONT_2 " m" MTITLE_2 "ⁱ" FRONT_2 "ⁿⁱˢʰᵉˡˡ " END, 
		FRONT_2 " " MTITLE_2 "ᵐ" FRONT_2 "ⁱⁿⁱˢʰᵉˡˡ " END, 
	};

	return (frames[frame]);
}


# define FRONT_3 "\033[48;5;16;1m"

const char *frame_bowling(unsigned int frame)
{
	const char	*frames[20] = {
		STYLE BG_CUSTOM "196" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "197" AND BOLD START "🎱inishell " END, 
		STYLE BG_CUSTOM "198" AND BOLD START " 🎱nishell " END, 
		STYLE BG_CUSTOM "199" AND BOLD START "  🎱ishell " END, 
		STYLE BG_CUSTOM "200" AND BOLD START "   🎱shell " END, 
		STYLE BG_CUSTOM "201" AND BOLD START "    🎱hell " END, 
		STYLE BG_CUSTOM "207" AND BOLD START "     🎱ell " END, 
		STYLE BG_CUSTOM "213" AND BOLD START "      🎱ll " END, 
		STYLE BG_CUSTOM "219" AND BOLD START "       🎱l " END, 
		STYLE BG_CUSTOM "225" AND BOLD START "        🎱 " END, 
		STYLE BG_CUSTOM "231" AND BOLD START "         🎱" END, 
		STYLE BG_CUSTOM "230" AND BOLD START "           " END, 
		STYLE BG_CUSTOM "229" AND BOLD START "           " END, 
		STYLE BG_CUSTOM "228" AND BOLD START "           " END, 
		STYLE BG_CUSTOM "227" AND BOLD START "     ₛ     " END, 
		STYLE BG_CUSTOM "226" AND BOLD START "   ₙᵢₛₕₑ   " END, 
		STYLE BG_CUSTOM "220" AND BOLD START " ₘᵢₙᵢₛₕₑₗₗ " END, 
		STYLE BG_CUSTOM "214" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "208" AND BOLD START " minishell " END, 
		STYLE BG_CUSTOM "202" AND BOLD START " minishell " END, 
	};

	return (frames[frame]);
}



