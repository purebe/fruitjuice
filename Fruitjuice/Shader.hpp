#pragma once

#include <GL\glew.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <direct.h>

namespace fruitjuice {
	enum class ShaderType { FRAG, VERT };

	class Shader {
	public:
		Shader();
		~Shader();

		void BuildFragment(const std::string &source);
		void BuildVertex(const std::string &source);
		void BuildShader(const std::string &fragSrc, const std::string &vertSrc);

		void BuildFragmentFromFile(const std::string &path);
		void BuildVertexFromFile(const std::string &path);
		void BuildShaderFromFile(const std::string &fragPath, const std::string &vertPath);

		void BuildShader();

		const GLint GetAttribLocation(const std::string& name) const;
		const GLint GetUniformLocation(const std::string& name) const;

		void EnableShader();
		void DisableShader();
	private:
		GLuint fragmentId, vertexId, programId;

		void compileShader(const GLuint shaderId, const std::string &source);
		void verifyShader(const GLuint shaderId);
		void verifyProgram();

		std::string readFile(const std::string &path);
	};
}