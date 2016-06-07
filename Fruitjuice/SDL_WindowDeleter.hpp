#pragma once

#include <SDL.h>

namespace fruitjuice {
	struct SDL_WindowDeleter {
		void operator ()(SDL_Window *window) {
			SDL_DestroyWindow(window);
		}
	};
}