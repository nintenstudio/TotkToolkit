#include <TotkToolkit/Rendering/Framebuffer.h>

#include <TotkToolkit/Rendering/DeviceFeatures.h>

#ifndef NDEBUG
#include <stdexcept>
#endif

namespace TotkToolkit::Rendering {
	Framebuffer::Framebuffer(GLenum target) : mTarget(target) {
		glGenFramebuffers(1, &mId);

		GLint maxColorAttachments;
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxColorAttachments);
		mColorAttachments.resize(maxColorAttachments);
		std::fill(mColorAttachments.begin(), mColorAttachments.end(), nullptr);
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &mId);
	}

	void Framebuffer::Bind() {
		glBindFramebuffer(mTarget, mId);

		switch (mTarget) {
		case GL_FRAMEBUFFER:
			mBoundFramebuffer = shared_from_this();
			break;
		case GL_READ_FRAMEBUFFER:
			mBoundReadFramebuffer = shared_from_this();
			break;
		case GL_DRAW_FRAMEBUFFER:
			mBoundDrawFramebuffer = shared_from_this();
			break;
		}
	}

	void Framebuffer::BindDefault(GLenum target) {
		glBindFramebuffer(target, 0);

		switch (target) {
		case GL_FRAMEBUFFER:
			mBoundFramebuffer = nullptr;
			break;
		case GL_READ_FRAMEBUFFER:
			mBoundReadFramebuffer = nullptr;
			break;
		case GL_DRAW_FRAMEBUFFER:
			mBoundDrawFramebuffer = nullptr;
			break;
		}
	}

	void Framebuffer::BindOrBindDefault(std::shared_ptr<Framebuffer> framebuffer, GLenum defaultTarget) {
		if (framebuffer == nullptr) {
			BindDefault(defaultTarget);
		}
		else {
			framebuffer->Bind();
		}
	}

	std::shared_ptr<Framebuffer> Framebuffer::GetBoundFrameBuffer() {
#ifndef NDEBUG
		GLint framebufferId;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebufferId);
		if (mBoundFramebuffer != nullptr && framebufferId != mBoundFramebuffer->GetId())
			std::runtime_error("Bound framebuffer doesn't match what the rendering system thinks it is! Always bind the framebuffer with Framebuffer::Bind().");
#endif

		return mBoundFramebuffer;
	}

	std::shared_ptr<Framebuffer> Framebuffer::GetBoundReadFrameBuffer() {
#ifndef NDEBUG
		GLint framebufferId;
		glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &framebufferId);
		if (mBoundFramebuffer != nullptr && framebufferId != mBoundFramebuffer->GetId())
			std::runtime_error("Bound read framebuffer doesn't match what the rendering system thinks it is! Always bind the framebuffer with Framebuffer::Bind().");
#endif

		return mBoundReadFramebuffer;
	}

	std::shared_ptr<Framebuffer> Framebuffer::GetBoundDrawFrameBuffer() {
#ifndef NDEBUG
		GLint framebufferId;
		glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &framebufferId);
		if (mBoundFramebuffer != nullptr && framebufferId != mBoundFramebuffer->GetId())
			std::runtime_error("Bound draw framebuffer doesn't match what the rendering system thinks it is! Always bind the framebuffer with Framebuffer::Bind().");
#endif

		return mBoundDrawFramebuffer;
	}

	void Framebuffer::AttachTexture(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment, GLint level) {
		std::shared_ptr<Framebuffer> boundFramebuffer;
		if (mTarget == GL_FRAMEBUFFER)
			boundFramebuffer = GetBoundFrameBuffer();
		else if (mTarget == GL_READ_FRAMEBUFFER)
			boundFramebuffer = GetBoundReadFrameBuffer();
		else if (mTarget == GL_DRAW_FRAMEBUFFER)
			boundFramebuffer = GetBoundDrawFrameBuffer();

		Bind();
		glFramebufferTexture(mTarget, attachment, texture->GetId(), level);
		SetAttachment(texture, attachment);
		BindOrBindDefault(boundFramebuffer, mTarget);
	}

	void Framebuffer::AttachTexture1D(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment, GLenum texTarget, GLint level) {
		std::shared_ptr<Framebuffer> boundFramebuffer;
		if (mTarget == GL_FRAMEBUFFER)
			boundFramebuffer = GetBoundFrameBuffer();
		else if (mTarget == GL_READ_FRAMEBUFFER)
			boundFramebuffer = GetBoundReadFrameBuffer();
		else if (mTarget == GL_DRAW_FRAMEBUFFER)
			boundFramebuffer = GetBoundDrawFrameBuffer();

		Bind();
		glFramebufferTexture1D(mTarget, attachment, texTarget, texture->GetId(), level);
		SetAttachment(texture, attachment);
		BindOrBindDefault(boundFramebuffer, mTarget);
	}

	void Framebuffer::AttachTexture2D(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment, GLenum texTarget, GLint level) {
		std::shared_ptr<Framebuffer> boundFramebuffer;
		if (mTarget == GL_FRAMEBUFFER)
			boundFramebuffer = GetBoundFrameBuffer();
		else if (mTarget == GL_READ_FRAMEBUFFER)
			boundFramebuffer = GetBoundReadFrameBuffer();
		else if (mTarget == GL_DRAW_FRAMEBUFFER)
			boundFramebuffer = GetBoundDrawFrameBuffer();

		Bind();
		glFramebufferTexture2D(mTarget, attachment, texTarget, texture->GetId(), level);
		SetAttachment(texture, attachment);
		BindOrBindDefault(boundFramebuffer, mTarget);
	}

	void Framebuffer::AttachTexture3D(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment, GLenum texTarget, GLint level, GLint layer) {
		std::shared_ptr<Framebuffer> boundFramebuffer;
		if (mTarget == GL_FRAMEBUFFER)
			boundFramebuffer = GetBoundFrameBuffer();
		else if (mTarget == GL_READ_FRAMEBUFFER)
			boundFramebuffer = GetBoundReadFrameBuffer();
		else if (mTarget == GL_DRAW_FRAMEBUFFER)
			boundFramebuffer = GetBoundDrawFrameBuffer();

		Bind();
		glFramebufferTexture3D(mTarget, attachment, texTarget, texture->GetId(), level, layer);
		SetAttachment(texture, attachment);
		BindOrBindDefault(boundFramebuffer, mTarget);
	}

	std::shared_ptr<TotkToolkit::Rendering::Texture> Framebuffer::GetAttachment(GLenum attachment) {
		if (attachment >= GL_COLOR_ATTACHMENT0 && attachment <= GL_COLOR_ATTACHMENT0 + TotkToolkit::Rendering::DeviceFeatures::GetMaxColorAttachments() - 1) {
			return mColorAttachments.at(attachment - GL_COLOR_ATTACHMENT0);
		}
		else if (attachment == GL_DEPTH_ATTACHMENT) {
			return mDepthAttachment;
		}
		else if (attachment == GL_STENCIL_ATTACHMENT) {
			return mStencilAttachment;
		}
		else if (attachment == GL_DEPTH_STENCIL_ATTACHMENT) {
			return mDepthStencilAttachment;
		}
	}

	void Framebuffer::SetAttachment(std::shared_ptr<TotkToolkit::Rendering::Texture> texture, GLenum attachment) {
		if (attachment >= GL_COLOR_ATTACHMENT0 && attachment <= GL_COLOR_ATTACHMENT0 + TotkToolkit::Rendering::DeviceFeatures::GetMaxColorAttachments() - 1) {
			mColorAttachments.at(attachment - GL_COLOR_ATTACHMENT0) = texture;
		}
		else if (attachment == GL_DEPTH_ATTACHMENT) {
			mDepthAttachment = texture;
		}
		else if (attachment == GL_STENCIL_ATTACHMENT) {
			mStencilAttachment = texture;
		}
		else if (attachment == GL_DEPTH_STENCIL_ATTACHMENT) {
			mDepthStencilAttachment = texture;
		}
	}

	std::shared_ptr<Framebuffer> Framebuffer::mBoundFramebuffer;
	std::shared_ptr<Framebuffer> Framebuffer::mBoundReadFramebuffer;
	std::shared_ptr<Framebuffer> Framebuffer::mBoundDrawFramebuffer;
}