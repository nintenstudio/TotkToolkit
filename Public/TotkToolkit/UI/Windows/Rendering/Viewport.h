#pragma once

#include <TotkToolkit/UI/Windows/Window.h>
#include <TotkToolkit/Rendering/Framebuffer.h>
#include <glad/glad.h>
#include <memory>

namespace TotkToolkit::UI::Windows::Rendering {
	class Viewport : public TotkToolkit::UI::Windows::Window {
public:
		Viewport(std::string name, bool* open);

		virtual void DrawContents() override;

protected:
		std::shared_ptr<TotkToolkit::Rendering::Framebuffer> mFramebuffer;
	};
}