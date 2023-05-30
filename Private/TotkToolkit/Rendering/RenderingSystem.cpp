#include <TotkToolkit/Rendering/RenderingSystem.h>

#include <TotkToolkit/Rendering/DeviceFeatures.h>
#include <TotkToolkit/Rendering/DebugMessageHandler.h>

namespace TotkToolkit::Rendering {
	void RenderingSystem::Init() {
		TotkToolkit::Rendering::DeviceFeatures::Init();
		TotkToolkit::Rendering::DebugMessageHandler::Init();
	}
}