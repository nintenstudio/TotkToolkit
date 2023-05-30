#pragma once

#include <TotkToolkit/Rendering/Texture.h>
#include <glad/glad.h>
#include <vector>
#include <memory>

namespace TotkToolkit::Rendering {
	/// <summary>
	/// Should always be created as an std::shared_ptr or things might go wrong.
	/// </summary>
	class Framebuffer : public std::enable_shared_from_this<Framebuffer> {
	public:
		Framebuffer();
		~Framebuffer();

		// If this object is nullptr the default framebuffer will be bound.
		void Bind(GLenum target);
		static void BindDefault(GLenum target);

		static std::shared_ptr<Framebuffer> GetBoundFrameBuffer();
		static std::shared_ptr<Framebuffer> GetBoundReadFrameBuffer();
		static std::shared_ptr<Framebuffer> GetBoundDrawFrameBuffer();

		void AttachTexture(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment, GLint level);
		void AttachTexture1D(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment, GLenum texTarget, GLint level);
		void AttachTexture2D(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment, GLenum texTarget, GLint level);
		void AttachTexture3D(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment, GLenum texTarget, GLint level, GLint layer);

		std::shared_ptr<TotkToolkit::Rendering::Texture> GetAttachment(GLenum attachment);

		inline GLuint GetId() { return mId; }
		inline GLenum GetTarget() { return mTarget; }

	protected:
		void SetAttachment(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment);

		GLuint mId;
		GLenum mTarget;

		std::vector<std::shared_ptr<TotkToolkit::Rendering::Texture>> mColorAttachments;
		std::shared_ptr <TotkToolkit::Rendering::Texture> mDepthAttachment;
		std::shared_ptr <TotkToolkit::Rendering::Texture> mStencilAttachment;
		std::shared_ptr <TotkToolkit::Rendering::Texture> mDepthStencilAttachment;

		static std::shared_ptr<Framebuffer> mBoundFramebuffer;
		static std::shared_ptr<Framebuffer> mBoundReadFramebuffer;
		static std::shared_ptr<Framebuffer> mBoundDrawFramebuffer;
	};
}