#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Shader.h"

class FrameBuffer
{
public:
	FrameBuffer(unsigned int numColourAttachments, bool createDepthTexture);
	~FrameBuffer() {};

	unsigned int getID() { return m_ID; }
	unsigned int getColourAttachment() { return textureColour; }
	unsigned int getDepthAttachment() { return textureDepth; }

	void bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_ID); }
	static void bindDefault() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	static void clear();


private:
	void createColourAttachment(bool doRbo);
	void createDepthAttachment();
	unsigned int m_ID;
	unsigned int m_numColourAttachments;
	unsigned int textureColour;
	unsigned int textureDepth;
};