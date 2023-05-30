#pragma once

#include <glad/glad.h>

namespace TotkToolkit::Rendering {
	class DeviceFeatures {
	public:
		static void Init();

		inline static GLint GetMaxColorAttachments() { return mMaxColorAttachments; }

	protected:
		static GLint mMaxColorAttachments;
	};
}