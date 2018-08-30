/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:56:37 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/30 09:30:59 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

// TODO: mouse rotation

static void	move_var(float *var, float amount,
	size_t scan_code_plus, size_t scan_code_minus)
{
	const Uint8		*kb_state = SDL_GetKeyboardState(NULL);

	if (kb_state[scan_code_plus])
		*var += amount;
	if (kb_state[scan_code_minus])
		*var -= amount;
}

static void	process_k_input(float secs, t_view_data *v)
{
	const Uint8		*kb_state = SDL_GetKeyboardState(NULL);
	const float		move_mult = kb_state[SDL_SCANCODE_LSHIFT] ? 10.0f : 2.5f;

	move_var(&v->rot.z, secs * 30.0f, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
	move_var(&v->rot.x, secs * 30.0f, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
	move_var(&v->pivot.z, move_mult * secs, SDL_SCANCODE_E, SDL_SCANCODE_Q);
	if (kb_state[SDL_SCANCODE_D] || kb_state[SDL_SCANCODE_A])
	{
		move_var(&v->pivot.x, move_mult * secs * cos_deg(v->rot.z),
			SDL_SCANCODE_D, SDL_SCANCODE_A);
		move_var(&v->pivot.y, move_mult * secs * sin_deg(v->rot.z),
			SDL_SCANCODE_D, SDL_SCANCODE_A);
	}
	if (kb_state[SDL_SCANCODE_W] || kb_state[SDL_SCANCODE_S])
	{
		move_var(&v->pivot.x, move_mult * secs * sin_deg(v->rot.z),
			SDL_SCANCODE_W, SDL_SCANCODE_S);
		move_var(&v->pivot.y, move_mult * secs * cos_deg(v->rot.z),
			SDL_SCANCODE_S, SDL_SCANCODE_W);
	}
}

int			controller_process_events(float elapsed_secs)
{
	SDL_Event	event;
	t_view_data	*v;

	v = view_get();
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
			(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
			return (1);
		if (event.type == SDL_MOUSEWHEEL)
		{
			v->distance = MAX(1.0f,
				v->distance - (float)event.wheel.y * elapsed_secs * 5.0f);
		}
	}
	process_k_input(elapsed_secs, v);
	return (0);
}
