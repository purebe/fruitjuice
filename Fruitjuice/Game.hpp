#pragma once

#include <memory>
#include <SDL.h>
#include <GL\glew.h>

#include "Shader.hpp"
#include "Model.hpp"

namespace fruitjuice {
	__declspec(align(16)) class Game {
	public:
		Game(std::shared_ptr<SDL_Window> ctx);
		virtual ~Game();

		// TODO: Determine the need to override 'operator new[]' and 'operator delete[]'
		void* operator new(size_t size);
		void operator delete(void *p);

		void run();
	private:
		std::shared_ptr<SDL_Window> window;
		SDL_Event event;
		Model model;
		Shader basic;
		bool running;

		void initGL();
		void handleInput();
		void update();
		void render();
	};
}