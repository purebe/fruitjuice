#include "Game.hpp"

namespace fruitjuice {
	Game::Game(std::shared_ptr<SDL_Window> ctx) : window(ctx), running(false), basic() {
		const std::string fragShaderPath = "shaders/basic.frag";
		const std::string vertShaderPath = "shaders/basic.vert";

		std::vector<const GLfloat> vertexData = {
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f
		};
		std::vector<const GLuint> indexData = {0, 1, 2, 3};

		basic.BuildShaderFromFile(fragShaderPath, vertShaderPath);

		model.LoadVertexData(vertexData);
		model.LoadIndexData(indexData);
		model.SetPositionLocation(basic.GetAttribLocation("position"));
		model.SetMVPLocation(basic.GetUniformLocation("projectionMatrix"), basic.GetUniformLocation("modelViewMatrix"));
	}

	Game::~Game() {
	}

	void* Game::operator new(size_t size) {
		if (size == 0) {
			size = 1;
		}

		void *mem = _aligned_malloc(size, 16);
		if (mem == nullptr) {
			throw std::bad_alloc();
		}

		return mem;
	}

	void Game::operator delete(void *mem) {
		if (mem == nullptr) {
			return;
		}

		_aligned_free(mem);
	}

	void Game::run() {
		running = true;
		initGL();

		while (running) {
			handleInput();
			update();
			render();

			SDL_GL_SwapWindow(window.get());
		}
	}

	void Game::initGL() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		/*glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	}

	void Game::handleInput() {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
	}

	void Game::update() {
		model.Tick();
	}

	void Game::render() {
		glClear(GL_COLOR_BUFFER_BIT);

		basic.EnableShader();
		model.Draw();
		basic.DisableShader();
	}
}