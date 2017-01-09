/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:50:40 by nboste            #+#    #+#             */
/*   Updated: 2017/01/09 23:56:39 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "types.h"

typedef struct	s_game
{
	int			cells[9];
	uint32		turn;
	int			winner;
}				t_game;

void	init_app(t_env *env);

int		process_app(void *env);

int		ai_turn(t_game *g);

t_bool	player_turn(t_env *e, t_game *g);

void	draw_cells(t_game *g, t_env *env);

int		check_winner(t_game *g);

void	draw_square(t_2ipair pos, uint32 size, uint32 color, t_env *env);
void	draw_cross(t_2ipair pos, uint32 size, uint32 color, t_env *env);

#endif
