#include "Game.hpp"

namespace fruitjuice {
	Game::Game() {
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

	void Game::Init(std::shared_ptr<SDL_Window> ctx) {
		this->window = ctx;
		camera.setFov(glm::radians(47.0f));
		camera.setAspectRatio(16.0f / 9.0f);
		camera.setLookat(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

		const std::string fragShaderPath = "shaders/basic.frag";
		const std::string vertShaderPath = "shaders/basic.vert";

		basic.BuildShaderFromFile(fragShaderPath, vertShaderPath);

		GLfloat positionX = -75.0f;
		GLfloat positionY = -47.0f;
		GLfloat deltaX    = 5.0f;
		GLfloat deltaY    = 10.0f;
		Model model;
		ModelImporter importer;
		importer.Import("models/potion.obj", basic, model);
		for (int itr = 0; itr < 29; ++itr) {
			for (int ktr = 0; ktr < 8; ++ktr) { 
				Model m(model);
				m.translate(glm::vec3(positionX + deltaX * (itr + 1), positionY + deltaY * (ktr + 1), 0));

				models.push_back(m);
			}
		}

		camera.translate(glm::vec3(0.0f, 0.0f, -50.0f));
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

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Game::handleInput() {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
	}

	void Game::update() {
		for (Model &m : models) {
			m.rotate(glm::radians(0.5f), glm::vec3(0, 1, 0));
		}

		if (zoom + zoomDelta >= 0.25f || zoom + zoomDelta <= -0.25f) {
			zoomDelta *= -1;
		}
		zoom += zoomDelta;

		camera.translate(glm::vec3(0.0f, 0.0f, zoom));
	}

	void Game::render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		basic.EnableShader();
		for (Model m : models) {
			m.Draw(camera);
		}
		basic.DisableShader(); 
	}
}