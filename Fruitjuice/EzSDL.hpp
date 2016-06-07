#pragma once

#include <memory>
#include <GL\glew.h>
#include <SDL.h>
#include "SDL_WindowDeleter.hpp"
#include "init_error_sdl.hpp"

namespace fruitjuice {
	class EzSDL {
	public:
		EzSDL(Uint32 flags = 0);
		~EzSDL();

		void CreateWindow(const std::string &title, const Uint32 width, const Uint32 height);
		void InitOpenGL();

		std::shared_ptr<SDL_Window> getWindow() const;
	private:
		std::shared_ptr<SDL_Window> window;
		SDL_GLContext glContext = nullptr;

		Uint32 width, height;

		void initGLContext();
		void initGLEW();
	};
}