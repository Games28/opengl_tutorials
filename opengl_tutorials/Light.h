#pragma once
#ifndef LIGHT_H
#define LIGHT_H


#include <glm.hpp>
#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <vector>

#include "ShadowMap.h"

class Light
{
public:
	Light();
	Light(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity,GLfloat dIntensity);

	ShadowMap* GetShadowMap() { return shadowMap; }
	

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
GLfloat diffuseIntensity;
glm::mat4 lightProj;

ShadowMap* shadowMap;

};

#endif // !LIGHT_H


