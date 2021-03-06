#pragma once

#include <memory>
#include <SDL.h>
#include <GL\glew.h>
#include <iostream>

#include "Camera.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "ModelImporter.hpp"

namespace fruitjuice {
	__declspec(align(16)) class Game {
	public:
		Game();
		virtual ~Game();

		// TODO: Determine the need to override 'operator new[]' and 'operator delete[]'
		void* operator new(size_t size);
		void operator delete(void *p);

		void Init(std::shared_ptr<SDL_Window> ctx);
		void run();
	private:
		std::shared_ptr<SDL_Window> window;
		SDL_Event event;
		std::vector<Model> models;
		Shader basic;
		Camera camera;
		bool running = false;

		GLfloat zoom = 0.0f;
		GLfloat zoomDelta = 0.01f;

		void initGL();
		void handleInput();
		void update();
		void render();
	};
}