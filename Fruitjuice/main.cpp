#define GLM_FORCE_RADIANS

#include <iostream>
#include <string>
#include <memory>
#include <GL\glew.h>

#include "EzSDL.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]) {
	fruitjuice::EzSDL sdl;
	fruitjuice::Game game;

	try {
		sdl.InitSDL(SDL_INIT_EVERYTHING);
		sdl.CreateWindow("Fruitjuice", 1280, 720);
		sdl.InitOpenGL();
		game.Init(sdl.getWindow());
	}
	catch (const std::exception &e) {
		std::cerr << "Unrecoverable exception thrown during startup: " << e.what() << std::endl;
		return 1;
	}

	try {
		game.run();
	}
	catch (const std::exception &e) {
		std::cerr << "Unhandled exception thrown during runtime: " << e.what() << std::endl;
	}

	return 0;
}