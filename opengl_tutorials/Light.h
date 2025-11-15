#pragma once
#ifndef LIGHT_H
#define LIGHT_H


#include <glm.hpp>
#include <GL/glew.h>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,GLfloat dIntensity);

	

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
GLfloat diffuseIntensity;


};

#endif // !LIGHT_H


