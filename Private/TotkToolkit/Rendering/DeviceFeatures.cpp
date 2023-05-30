#include <TotkToolkit/Rendering/DeviceFeatures.h>

#include <glad/glad.h>

namespace TotkToolkit::Rendering {
	void DeviceFeatures::Init() {
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &mMaxColorAttachments);
	}

	GLint DeviceFeatures::mMaxColorAttachments;
}