/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:02:49 by pohl              #+#    #+#             */
/*   Updated: 2020/03/01 16:55:48 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H

# define DEBUG_H

# include <stdio.h>
# include <unistd.h>

# define DP(x)	printf("%p\n", x)
# define DD(x)	printf("%d\n", x)
# define DS(x)	printf("%s\n", x)
# define DF(x)	printf("%f\n", x)

#endif
