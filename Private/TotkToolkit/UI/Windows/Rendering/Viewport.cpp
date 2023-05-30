#include <TotkToolkit/UI/Windows/Rendering/Viewport.h>

#include <TotkToolkit/Rendering/Texture.h>
#include <imgui.h>
#include <glad/glad.h>
#include <memory>

namespace TotkToolkit::UI::Windows::Rendering {
	Viewport::Viewport(std::string name, bool* open) : TotkToolkit::UI::Windows::Window(name, open), mFramebuffer(std::make_shared<TotkToolkit::Rendering::Framebuffer>(GL_FRAMEBUFFER)) {
		std::shared_ptr<TotkToolkit::Rendering::Texture> texture = std::make_shared<TotkToolkit::Rendering::Texture>();
		texture->Init2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		texture->SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture->SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		mFramebuffer->AttachTexture2D(texture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0);
	}

	void Viewport::DrawContents() {
		ImVec2 windowContentRegionSize;
		{
			ImVec2 windowContentRegionMin = ImGui::GetWindowContentRegionMin();
			ImVec2 windowContentRegionMax = ImGui::GetWindowContentRegionMax();

			windowContentRegionSize.x = windowContentRegionMax.x - windowContentRegionMin.x;
			windowContentRegionSize.y = windowContentRegionMax.y - windowContentRegionMin.y;
		}

		mFramebuffer->Bind();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		ImGui::Image((void*)(intptr_t)mFramebuffer->GetAttachment(GL_COLOR_ATTACHMENT0)->GetId(), windowContentRegionSize, ImVec2(0, 1), ImVec2(1, 0));
	}
}