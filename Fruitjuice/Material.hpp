#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <string>
#include <enum_flags.h>

ENUM_FLAGS(Lighting)
enum class Lighting {
	Color    = 0x01,
	Ambient  = 0x02,
	Specular = 0x04
};

struct Material {
	Material() { }
	Material(const std::string &name, 
		const glm::vec3 &ambient, 
		const glm::vec3 &diffuse, 
		const glm::vec3 &specular, 
		const GLfloat &specularExponent, 
		const GLfloat &opacity, 
		const Lighting &lightMode) : 
		name(name),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		specularExponent(specularExponent),
		opacity(opacity),
		lightMode(lightMode) { 
	}

	static Lighting parseLightingMode(std::string lightingMode) {
		Lighting mode;
		int imode = std::stoi(lightingMode);
		switch (imode) {
		case 0:
			mode = Lighting::Color;
			break;
		case 1:
			mode = Lighting::Color | Lighting::Ambient;
			break;
		case 2:
			mode = Lighting::Color | Lighting::Ambient | Lighting::Specular;
			break;
		}

		return mode;
	}

	std::string name;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat specularExponent;
	GLfloat opacity;
	Lighting lightMode;
};