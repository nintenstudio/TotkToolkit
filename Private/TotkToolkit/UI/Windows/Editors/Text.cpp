#include <TotkToolkit/UI/Windows/Editors/Text.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>

int inputTextCallback(ImGuiInputTextCallbackData* data) {
    ((std::string*)(data->UserData))->resize(data->BufSize);
    return 1;
}

namespace TotkToolkit::UI::Windows::Editors {
    Text::Text(std::string name) : TotkToolkit::UI::Windows::Window(name) {
        
    }

    void Text::DrawContents() {
        ImGui::InputTextMultiline(ImGuiItem::AppendIdentifier("##InputText").c_str(), &mText[0], mText.size(), ImVec2(0, 0), ImGuiInputTextFlags_CallbackResize, &inputTextCallback, &mText);
    }
}