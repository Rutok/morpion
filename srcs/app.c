/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:50:35 by nboste            #+#    #+#             */
/*   Updated: 2017/01/10 00:14:35 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "error.h"
#include "drawer.h"

static void	print_fps(void)
{
	static int time;
	static int fps;

	fps++;
	if (!time)
		time = SDL_GetTicks();
	if (SDL_GetTicks() >= (Uint32)time + 1000)
	{
		ft_putstr("FPS : ");
		ft_putnbr(fps);
		ft_putchar('\n');
		fps = 0;
		time = SDL_GetTicks();
	}
}

void	init_app(t_env *env)
{
	t_game	*game;
	int		i;

	if (!(game = (t_game *)malloc(sizeof(t_game))))
		ft_exit("Not enough memory.");
	i = 0;
	while (i < 9)
		game->cells[i++] = 0;
	game->turn = 0;
	game->winner = 0;
	env->app.d = (void *)game;
}

void	draw_grid(t_env *env)
{
	int		x;
	int		y;

	x = 0;
	y = env->rend.size.y / 3;
	while (x < env->rend.size.x)
		drawer_put_pixel((t_2ipair){x++, y}, 0xffffffff, &env->rend);
	x = 0;
	y *= 2;
	while (x < env->rend.size.x)
		drawer_put_pixel((t_2ipair){x++, y}, 0xffffffff, &env->rend);
	x = env->rend.size.x / 3;
	y = 0;
	while (y < env->rend.size.y)
		drawer_put_pixel((t_2ipair){x, y++}, 0xffffffff, &env->rend);
	x *= 2;
	y = 0;
	while (y < env->rend.size.y)
		drawer_put_pixel((t_2ipair){x, y++}, 0xffffffff, &env->rend);
}

int		process_app(void *env)
{
	t_env	*e = (t_env *)env;
	t_game	*g = (t_game *)e->app.d;
	uint32	lt;

	draw_grid(e);
	e->event.draw = 1;
	drawer_wait_copy(e);
	while (!e->event.exit)
	{
		print_fps();
		lt = g->turn;
		if (g->turn % 2)
		{
			// PC
		//	SDL_Delay(100);
			if (ai_turn(g))
				g->turn++;
		}
		else if (e->event.mouse_click)
		{
			// Player
			if (player_turn(e, g))
				g->turn++;
			e->event.mouse_click = 0;
		}
		if (lt != g->turn)
		{
			g->winner = check_winner(g);
			e->event.draw = 1;
			draw_grid(e);
			draw_cells(g, e);
			drawer_wait_copy(e);
		}
	}
	return (0);
}

int		ai_turn(t_game *g)
{
	int		i;

	i = 0;
	while (i < 9)
	{
		if (!g->cells[i])
		{
			g->cells[i] = -1;
			return (1);
		}
		i++;
	}
	return (0);
}

t_bool	player_turn(t_env *env, t_game *g)
{
	t_2ipair	target;
	uint32		cell;

	target.x = (double)env->event.mouse_pos.x / (double)env->rend.size.x * 3;
	target.y = (double)env->event.mouse_pos.y / (double)env->rend.size.y * 3;
	cell = target.x + target.y * 3;
	if (g->cells[cell])
		return (0);
	g->cells[cell] = 1;
	return (1);
}

void	draw_cells(t_game *g, t_env *env)
{
	uint	i;

	i = 0;
	while (i < 9)
	{
		if (g->cells[i] == -1)
			draw_square((t_2ipair)
			{
				env->rend.size.x / 6 * ((i % 3) * 2 + 1),
				env->rend.size.y / 6 * ((i / 3) * 2 + 1)
			}, env->rend.size.x * 0.28, 0xcc5555ff, env);
		else if (g->cells[i] == 1)
			draw_cross((t_2ipair)
			{
				env->rend.size.x / 6 * ((i % 3) * 2 + 1),
				env->rend.size.y / 6 * ((i / 3) * 2 + 1)
			}, env->rend.size.x * 0.28, 0x5555ccff, env);
		++i;
	}
}

int		check_line(t_game *g, uint32 n)
{
	return ((g->cells[n * 3] + g->cells[1 + n * 3] + g->cells[2 + n * 3]) / 3);
}

int		check_winner(t_game *g)
{
	printf("Line 0: %d\n", check_line(g, 0));
	printf("Line 1: %d\n", check_line(g, 1));
	printf("Line 2: %d\n", check_line(g, 2));
	return (0);
}
