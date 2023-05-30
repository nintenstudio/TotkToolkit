#pragma once

#include <TotkToolkit/Rendering/Texture.h>

namespace TotkToolkit::Rendering {
	Texture::Texture() {
		glGenTextures(1, &mId);
	}
	Texture::~Texture() {
		glDeleteTextures(1, &mId);
	}

	void Texture::Bind() {
		glBindTexture(mTarget, mId);
	}

	void Texture::Init1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid* data) {
		mTarget = target;
		Bind();
		glTexImage1D(target, level, internalFormat, width, 0, format, type, data);
	}

	void Texture::Init2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data) {
		mTarget = target;
		Bind();
		glTexImage2D(target, level, internalFormat, width, height, 0, format, type, data);
	}

	void Texture::Init3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data) {
		mTarget = target;
		Bind();
		glTexImage3D(target, level, internalFormat, width, height, depth, 0, format, type, data);
	}

	void Texture::Init2DMultisample(GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) {
		mTarget = target;
		Bind();
		glTexImage2DMultisample(target, samples, internalFormat, width, height, fixedSampleLocations);
	}

	void Texture::Init3DMultisample(GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations) {
		mTarget = target;
		Bind();
		glTexImage3DMultisample(target, samples, internalFormat, width, height, depth, fixedSampleLocations);
	}

	void Texture::SetParameter(GLenum name, GLint value) {
		glTexParameteri(mTarget, name, value);
	}
	void Texture::SetParameter(GLenum name, GLfloat value) {
		glTexParameterf(mTarget, name, value);
	}
	void Texture::SetParameters(GLenum name, GLint* values) {
		glTexParameteriv(mTarget, name, values);
	}
	void Texture::SetParameters(GLenum name, GLfloat* values) {
		glTexParameterfv(mTarget, name, values);
	}
	// Same as SetParameters(GLenum name, GLint* values), except the values are not internally converted to float and are treated as ints.
	void Texture::SetParametersI(GLenum name, GLint* values) {
		glTexParameterIiv(mTarget, name, values);
	}
	// Same as SetParameters(GLenum name, GLint* values), except the values are not internally converted to float and are treated as uints.
	void Texture::SetParametersIu(GLenum name, GLuint* values) {
		glTexParameterIuiv(mTarget, name, values);
	}
}