#include "EzSDL.hpp"

namespace fruitjuice {
	EzSDL::EzSDL() {
	}

	EzSDL::~EzSDL() {
		if (glContext != nullptr) {
			SDL_GL_DeleteContext(glContext);
		}

		if (sdlInit) {
			SDL_Quit();
		}
	}

	void EzSDL::InitSDL(Uint32 flags) {
		if (SDL_Init(flags) != 0) {
			throw init_error_sdl();
		}
		sdlInit = true;
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	}

	void EzSDL::CreateWindow(const std::string &title, const Uint32 width, const Uint32 height) {
		window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, SDL_WINDOW_OPENGL), SDL_DestroyWindow);
		this->width = width;
		this->height = height;

		if (!window) {
			throw init_error_sdl();
		}
	}

	void EzSDL::InitOpenGL() {
		initGLContext();
		initGLEW();

		if (SDL_GL_SetSwapInterval(1) == -1) {
			throw init_error_sdl();
		}

		glViewport(0, 0, width, height);

		std::cerr << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	}

	void EzSDL::initGLContext() {
		glContext = SDL_GL_CreateContext(window.get());

		if (glContext == NULL) {
			throw init_error_sdl();
		}
	}

	void EzSDL::initGLEW() {
		glewExperimental = true;
		GLenum result = glewInit();

		if (result != GLEW_OK) {
			throw init_error(std::string(reinterpret_cast<const char*>(glewGetErrorString(result))));
		}
	}

	std::shared_ptr<SDL_Window> EzSDL::getWindow() const {
		return window;
	}
}