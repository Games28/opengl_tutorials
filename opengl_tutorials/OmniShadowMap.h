#pragma once
#ifndef OMNISHADOWMAP_H
#define OMNISHADOWMAP_H
#include "ShadowMap.h"

class OmniShadowMap : public ShadowMap
{
public:
	OmniShadowMap();

	bool Init(unsigned int width, unsigned int height) override;

	void Write() override;

	void Read(GLenum TextureUnit) override;

	~OmniShadowMap();


private:


};


#endif // !OMNISHADOWMAP_H



