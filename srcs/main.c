/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:27 by mhoosen           #+#    #+#             */
/*   Updated: 2018/09/18 16:03:12 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

static void	die(int code, char *pre_msg)
{
	if (pre_msg)
		ft_putstr_fd(pre_msg, 2);
	if (code)
		ft_putendl_fd(SDL_GetError(), 2);
	view_free();
	model_free();
	SDL_Quit();
	exit(code);
}

static void	loop(void)
{
	while (1)
	{
		if (controller_process_events(0.3f))
			break ;
		view_update();
	}
}

int			main(int ac, char **av)
{
	if (ac <= 1)
		die(1, "No scene file provided");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		die(2, "Failed to initialize SDL: ");
	if (model_init(av[1]))
		die(3, NULL);
	if (view_init(800, 600, 90.0f))
		die(4, NULL);
	loop();
	die(0, NULL);
	return (0);
}
