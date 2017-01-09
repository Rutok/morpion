/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 12:37:05 by nboste            #+#    #+#             */
/*   Updated: 2017/01/08 15:51:33 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "app.h"

int		main(int argc, char **argv)
{
	t_env	env;

	env.app.argc = argc;
	env.app.argv = argv;
	env.win.name = ft_strdup("morpion");
	env.win.size.x = 720;
	env.win.size.y = 720;
	engine_init(&env, &init_app, &process_app, NULL);
	return (engine_run(&env));
}
