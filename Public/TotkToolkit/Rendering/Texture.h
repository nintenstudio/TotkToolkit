#pragma once

#include <glad/glad.h>

namespace TotkToolkit::Rendering {
	class Texture {
	public:
		Texture();
		~Texture();

		void Bind();

		void Init1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid* data);
		void Init2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data);
		void Init3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data);
		void Init2DMultisample(GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations);
		void Init3DMultisample(GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations);

		void SetParameter(GLenum name, GLint value);
		void SetParameter(GLenum name, GLfloat value);
		void SetParameters(GLenum name, GLint* values);
		void SetParameters(GLenum name, GLfloat* values);
		// Same as SetParameters(GLenum name, GLint* values), except the values are not internally converted to float and are treated as ints.
		void SetParametersI(GLenum name, GLint* values);
		// Same as SetParameters(GLenum name, GLint* values), except the values are not internally converted to float and are treated as uints.
		void SetParametersIu(GLenum name, GLuint* values);

		inline GLuint GetId() { return mId; }
		inline GLenum GetTarget() { return mTarget; }

	protected:
		GLuint mId;
		GLenum mTarget;
	};
}