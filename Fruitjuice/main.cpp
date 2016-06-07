#include <iostream>
#include <string>
#include <memory>
#include <GL\glew.h>

#include "EzSDL.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]) {
	std::unique_ptr<fruitjuice::EzSDL> sdl;
	std::unique_ptr<fruitjuice::Game> game;

	try {
		sdl = std::make_unique<fruitjuice::EzSDL>(SDL_INIT_EVERYTHING);
		sdl->CreateWindow("Fruitjuice", 1280, 720);
		sdl->InitOpenGL();
		game = std::make_unique<fruitjuice::Game>(sdl->getWindow());
	}
	catch (const std::exception &e) {
		std::cerr << "Unrecoverable exception thrown during startup: " << e.what() << std::endl;
		return 1;
	}

	try {
		game->run();
	}
	catch (const std::exception &e) {
		std::cerr << "Unhandled exception thrown during runtime: " << e.what() << std::endl;
	}

	return 0;
}