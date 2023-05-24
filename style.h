/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:12:53 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/05 10:12:57 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STYLE_H
# define STYLE_H

# include <stdio.h>

// color
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

// bold color
# define BOLD_BLACK "\033[1;30m"
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_PURPLE "\033[1;35m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_WHITE "\033[1;37m"

// background
# define BACK_BLACK "\033[0;40m"
# define BACK_RED "\033[0;41;30m"
# define BACK_GREEN "\033[0;42;30m"
# define BACK_YELLOW "\033[0;43;30m"
# define BACK_BLUE "\033[0;44;30m"
# define BACK_PURPLE "\033[0;45;30m"
# define BACK_CYAN "\033[0;46;30m"
# define BACK_WHITE "\033[0;47;30m"

# define BACK_BOLD_BLACK "\033[1;40m"
# define BACK_BOLD_RED "\033[1;41;30m"
# define BACK_BOLD_GREEN "\033[1;42;30m"
# define BACK_BOLD_YELLOW "\033[1;43;30m"
# define BACK_BOLD_BLUE "\033[1;44;30m"
# define BACK_BOLD_PURPLE "\033[1;45;30m"
# define BACK_BOLD_CYAN "\033[1;46;30m"
# define BACK_BOLD_WHITE "\033[1;47;30m"

// underline color
# define UNDERLINE_BLACK "\033[4;30m"
# define UNDERLINE_RED "\033[4;31m"
# define UNDERLINE_GREEN "\033[4;32m"
# define UNDERLINE_YELLOW "\033[4;33m"
# define UNDERLINE_BLUE "\033[4;34m"
# define UNDERLINE_PURPLE "\033[4;35m"
# define UNDERLINE_CYAN "\033[4;36m"
# define UNDERLINE_WHITE "\033[4;37m"
# define RESET "\033[0m"
# define RST "\033[0m"

#endif