/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:27 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/29 17:23:18 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

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
	Uint32		last_ticks;
	ssize_t		elapsed_ticks;
	float		elapsed_secs;

	last_ticks = SDL_GetTicks();
	while (1)
	{
		elapsed_ticks = SDL_GetTicks() - last_ticks;
		last_ticks = SDL_GetTicks();
		elapsed_secs = (float)elapsed_ticks / 1000.0f;
		if (controller_process_events(elapsed_secs))
			break ;
		//model_update(elapsed_ticks, elapsed_secs);
		view_update();
	}
}

int			main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		die(2, "Failed to initialize SDL: ");
	if (model_init())
		die(3, NULL);
	if (view_init(800, 600, 90.0f))
		die(4, NULL);
	loop();
	die(0, NULL);
	return (0);
}