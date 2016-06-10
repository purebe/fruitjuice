#include "Shader.hpp"

namespace fruitjuice {
	Shader::Shader() : programId(0), fragmentId(0), vertexId(0) {
	}

	Shader::~Shader() {
		if (programId > 0) {
			glDeleteProgram(programId);
		}
	}

	void Shader::BuildFragment(const std::string &source) {
		fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
		if (!glIsShader(fragmentId)) {
			throw std::exception("Fragment shader could not be created.");
		}
		compileShader(fragmentId, source);
	}

	void Shader::BuildVertex(const std::string &source) {
		vertexId = glCreateShader(GL_VERTEX_SHADER);
		if (!glIsShader(vertexId)) {
			throw std::exception("Vertex shader could not be created.");
		}
		compileShader(vertexId, source);
	}

	void Shader::BuildShader() {
		if (fragmentId == 0 && vertexId == 0) {
			throw std::exception("Cannot build shader program with a missing fragment or vertex shader.");
		}

		programId = glCreateProgram();
		glAttachShader(programId, fragmentId);
		glAttachShader(programId, vertexId);

		glLinkProgram(programId);

		glDetachShader(programId, vertexId);
		glDetachShader(programId, fragmentId);
		glDeleteShader(fragmentId);
		glDeleteShader(vertexId);

		verifyProgram();
	}

	void Shader::BuildFragmentFromFile(const std::string &path) {
		BuildFragment(FileIO::readFile(path));
	}

	void Shader::BuildVertexFromFile(const std::string &path) {
		BuildVertex(FileIO::readFile(path));
	}

	void Shader::BuildShaderFromFile(const std::string &fragPath, const std::string &vertPath) {
		BuildFragmentFromFile(fragPath);
		BuildVertexFromFile(vertPath);
		BuildShader();
	}
	
	void Shader::BuildShader(const std::string &fragSrc, const std::string &vertSrc) {
		BuildFragment(fragSrc);
		BuildVertex(vertSrc);
		BuildShader();
	}

	void Shader::compileShader(const GLuint shaderId, const std::string &source) {
		const GLchar *src = source.c_str();
		GLint srcLength = source.size();

		glShaderSource(shaderId, 1, &src, &srcLength);
		glCompileShader(shaderId);
		verifyShader(shaderId);
	}

	void Shader::verifyShader(const GLuint shaderId) {
		GLint success = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {
			GLint logSize = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

			std::vector<GLchar> infoLog(logSize);
			if (logSize > 0) {
				glGetShaderInfoLog(shaderId, logSize, nullptr, &infoLog[0]);
				glDeleteShader(shaderId);
				throw std::exception(std::string(infoLog.begin(), infoLog.end()).c_str());
			}
			else {
				glDeleteShader(shaderId);
				throw std::exception("Shader failed to compile, no log provided.");
			}
		}
	}

	void Shader::verifyProgram() {
		GLint success = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, &success);

		if (success == GL_FALSE) {
			GLint logSize = 0;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

			std::vector<GLchar> infoLog(logSize);
			if (logSize > 0) {
				glGetProgramInfoLog(programId, logSize, nullptr, &infoLog[0]);
				glDeleteProgram(programId);
				throw std::exception(std::string(infoLog.begin(), infoLog.end()).c_str());
			}
			else {
				glDeleteProgram(programId);
				throw std::exception("Program failed to link, no log provided.");
			}
		}
	}

	const GLint Shader::GetAttribLocation(const std::string& name) const {
		return glGetAttribLocation(programId, name.c_str());
	}

	const GLint Shader::GetUniformLocation(const std::string& name) const {
		return glGetUniformLocation(programId, name.c_str());
	}

	void Shader::EnableShader() {
		glUseProgram(programId);
	}

	void Shader::DisableShader() {
		glUseProgram(0);
	}
}