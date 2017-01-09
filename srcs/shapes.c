/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 16:48:14 by nboste            #+#    #+#             */
/*   Updated: 2017/01/08 17:53:40 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawer.h"

void	draw_square(t_2ipair pos, uint32 size, uint32 color, t_env *env)
{
	t_2ipair	tmp;

	pos.x -= size / 2;
	pos.y -= size / 2;
	tmp = pos;
	while (tmp.x < pos.x + (int)size)
	{
		drawer_put_pixel((t_2ipair){tmp.x, pos.y}, color, &env->rend);
		drawer_put_pixel((t_2ipair){tmp.x, pos.y + size}, color, &env->rend);
		++tmp.x;
	}
	while (tmp.y < pos.y + (int)size)
	{
		drawer_put_pixel((t_2ipair){pos.x, tmp.y}, color, &env->rend);
		drawer_put_pixel((t_2ipair){pos.x + size, tmp.y}, color, &env->rend);
		++tmp.y;
	}
}

void	draw_cross(t_2ipair pos, uint32 size, uint32 color, t_env *env)
{
	uint32	tmp;

	pos.x -= size / 2;
	pos.y -= size / 2;
	tmp = size;
	while (size)
	{
		drawer_put_pixel((t_2ipair){pos.x + size, pos.y + size}, color, &env->rend);
		drawer_put_pixel((t_2ipair){pos.x + size, pos.y + tmp - size}, color, &env->rend);
		--size;
	}
}
