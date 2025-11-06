/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:01:33 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/06 14:55:50 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*frame_fish(unsigned int frame)
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

const char	*frame_upercase(unsigned int frame)
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

const char	*frame_moving_tile(unsigned int frame)
{
	const char	*frames[20] = {
		M_TILE_FRONT "" M_TILE_MTITLE " " M_TILE_FRONT "minishell " END,
		M_TILE_FRONT " " M_TILE_MTITLE "m" M_TILE_FRONT "inishell " END,
		M_TILE_FRONT " m" M_TILE_MTITLE "i" M_TILE_FRONT "nishell " END,
		M_TILE_FRONT " mi" M_TILE_MTITLE "n" M_TILE_FRONT "ishell " END,
		M_TILE_FRONT " min" M_TILE_MTITLE "i" M_TILE_FRONT "shell " END,
		M_TILE_FRONT " mini" M_TILE_MTITLE "s" M_TILE_FRONT "hell " END,
		M_TILE_FRONT " minis" M_TILE_MTITLE "h" M_TILE_FRONT "ell " END,
		M_TILE_FRONT " minish" M_TILE_MTITLE "e" M_TILE_FRONT "ll " END,
		M_TILE_FRONT " minishe" M_TILE_MTITLE "l" M_TILE_FRONT "l " END,
		M_TILE_FRONT " minishel" M_TILE_MTITLE "l" M_TILE_FRONT " " END,
		M_TILE_FRONT " minishell" M_TILE_MTITLE " " M_TILE_FRONT "" END,
		M_TILE_FRONT " minishel" M_TILE_MTITLE "l" M_TILE_FRONT " " END,
		M_TILE_FRONT " minishe" M_TILE_MTITLE "l" M_TILE_FRONT "l " END,
		M_TILE_FRONT " minish" M_TILE_MTITLE "e" M_TILE_FRONT "ll " END,
		M_TILE_FRONT " minis" M_TILE_MTITLE "h" M_TILE_FRONT "ell " END,
		M_TILE_FRONT " mini" M_TILE_MTITLE "s" M_TILE_FRONT "hell " END,
		M_TILE_FRONT " min" M_TILE_MTITLE "i" M_TILE_FRONT "shell " END,
		M_TILE_FRONT " mi" M_TILE_MTITLE "n" M_TILE_FRONT "ishell " END,
		M_TILE_FRONT " m" M_TILE_MTITLE "i" M_TILE_FRONT "nishell " END,
		M_TILE_FRONT " " M_TILE_MTITLE "m" M_TILE_FRONT "inishell " END,
	};

	return (frames[frame]);
}

const char	*frame_smallcase(unsigned int frame)
{
	const char	*frames[20] = {
		SMALL_FRONT "" SMALL_MITLE " " SMALL_FRONT "ᵐⁱⁿⁱˢʰᵉˡˡ " END,
		SMALL_FRONT " " SMALL_MITLE "ᵐ" SMALL_FRONT "ⁱⁿⁱˢʰᵉˡˡ " END,
		SMALL_FRONT " m" SMALL_MITLE "ⁱ" SMALL_FRONT "ⁿⁱˢʰᵉˡˡ " END,
		SMALL_FRONT " mi" SMALL_MITLE "ⁿ" SMALL_FRONT "ⁱˢʰᵉˡˡ " END,
		SMALL_FRONT " min" SMALL_MITLE "ⁱ" SMALL_FRONT "ˢʰᵉˡˡ " END,
		SMALL_FRONT " mini" SMALL_MITLE "ˢ" SMALL_FRONT "ʰᵉˡˡ " END,
		SMALL_FRONT " minis" SMALL_MITLE "ʰ" SMALL_FRONT "ᵉˡˡ " END,
		SMALL_FRONT " minish" SMALL_MITLE "ᵉ" SMALL_FRONT "ˡˡ " END,
		SMALL_FRONT " minishe" SMALL_MITLE "ˡ" SMALL_FRONT "ˡ " END,
		SMALL_FRONT " minishel" SMALL_MITLE "ˡ" SMALL_FRONT " " END,
		SMALL_FRONT " minishell" SMALL_MITLE " " SMALL_FRONT "" END,
		SMALL_FRONT " minishel" SMALL_MITLE "ˡ" SMALL_FRONT " " END,
		SMALL_FRONT " minishe" SMALL_MITLE "ˡ" SMALL_FRONT "ˡ " END,
		SMALL_FRONT " minish" SMALL_MITLE "ᵉ" SMALL_FRONT "ˡˡ " END,
		SMALL_FRONT " minis" SMALL_MITLE "ʰ" SMALL_FRONT "ᵉˡˡ " END,
		SMALL_FRONT " mini" SMALL_MITLE "ˢ" SMALL_FRONT "ʰᵉˡˡ " END,
		SMALL_FRONT " min" SMALL_MITLE "ⁱ" SMALL_FRONT "ˢʰᵉˡˡ " END,
		SMALL_FRONT " mi" SMALL_MITLE "ⁿ" SMALL_FRONT "ⁱˢʰᵉˡˡ " END,
		SMALL_FRONT " m" SMALL_MITLE "ⁱ" SMALL_FRONT "ⁿⁱˢʰᵉˡˡ " END,
		SMALL_FRONT " " SMALL_MITLE "ᵐ" SMALL_FRONT "ⁱⁿⁱˢʰᵉˡˡ " END,
	};

	return (frames[frame]);
}

const char	*frame_bowling(unsigned int frame)
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
