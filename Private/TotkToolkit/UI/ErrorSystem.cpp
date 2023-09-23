#include <TotkToolkit/UI/ErrorSystem.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>

namespace TotkToolkit::UI {
    void ErrorSystem::Init() {
        TotkToolkit::Messaging::NoticeBoard::AddReceiver(&sExternalReceiver);
    }

    void ErrorSystem::Draw() {
        std::shared_lock<std::shared_mutex> lock(sMessagesMutex);
        if (sMessages.size() != 0) {
            static bool windowOpen = true;
            ImGui::Begin(TotkToolkit::UI::Localization::TranslationSource::GetText("ERROR"), &windowOpen);

            for (std::string message : sMessages) {
                ImGui::Text(message.c_str());
            }

            ImGui::End();

            if (!windowOpen) {
                sMessages.clear();
                windowOpen = true;
            }
        }
    }

    std::vector<std::string> ErrorSystem::sMessages; std::shared_mutex ErrorSystem::sMessagesMutex;
    TotkToolkit::Messaging::ExternalReceivers::UI::ErrorSystem ErrorSystem::sExternalReceiver;
}