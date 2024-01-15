#include "FrameBuffer.h"
#include <iostream>
#include "scene.h"


FrameBuffer::FrameBuffer(unsigned int numColourAttachments, bool createDepthTexture)
{
	m_numColourAttachments = numColourAttachments;
	if (m_numColourAttachments > 0 && !createDepthTexture)
	{
		createColourAttachment(true);
	}
	else if (m_numColourAttachments > 0 && createDepthTexture)
	{
		createColourAttachment(false);
		//createDepthAttachment();
	}
	else
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
}

void FrameBuffer::clear()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::createColourAttachment(bool doRbo)
{
	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	glGenTextures(1, &textureColour);
	glBindTexture(GL_TEXTURE_2D, textureColour);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColour, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S = x axis 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T == y axis, R if 3D
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (doRbo)
	{
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	}
	else if (!doRbo)
	{
		//glGenFramebuffers(1, &m_ID);
		//glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		glGenTextures(1, &textureDepth);
		glBindTexture(GL_TEXTURE_2D, textureDepth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepth, 0);
	}
	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Frame buffer creation failed with ";

		switch (status)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			std::cerr << "GL_FRAMEBUFFER_UNDEFINED";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
			break;

		case GL_FRAMEBUFFER_UNSUPPORTED:
			std::cerr << "GL_FRAMEBUFFER_UNSUPPORTED";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
			break;

		default:
			std::cerr << "an unknown error: " << status;
			break;
		}

		std::cerr << std::endl;
	}

}

void FrameBuffer::createDepthAttachment()
{
	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	glGenTextures(1, &textureDepth);
	glBindTexture(GL_TEXTURE_2D, textureDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepth, 0);

	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Frame buffer creation failed with ";

		switch (status)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			std::cerr << "GL_FRAMEBUFFER_UNDEFINED";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
			break;

		case GL_FRAMEBUFFER_UNSUPPORTED:
			std::cerr << "GL_FRAMEBUFFER_UNSUPPORTED";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
			break;

		default:
			std::cerr << "an unknown error: " << status;
			break;
		}

		std::cerr << std::endl;
	}
}
