#include <TotkToolkit/UI/Windows/Editors/Text.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace TotkToolkit::UI::Windows::Editors {
    Text::Text(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::UI::Windows::Editor(fileHandle, name, open) {
        
    }

    void Text::Draw() {
        if (mTextEditor.IsTextChanged()) {
            if (mTextEditor.GetText() != mSavedText)
                mTextEditorModified = true;
            else
                mTextEditorModified = false;
        }

        bool unCollapsed;
        if (mTextEditorModified)
            unCollapsed = ImGui::Begin(AppendExclusiveIdentifier(mName + "*").c_str(), mOpen);
        else
            unCollapsed = ImGui::Begin(AppendExclusiveIdentifier(mName).c_str(), mOpen);
        if (unCollapsed) {
            DrawContents();
        }
        ImGui::End();
    }

    void Text::DrawContents() {
        ImVec2 toolbarCursorStart = ImGui::GetCursorPos();
        // Any sort of toolbar code can be put here.
        ImVec2 toolbarCursorEnd = ImGui::GetCursorPos();

        ImVec2 windowContentRegionSize;
        {
            ImVec2 windowContentRegionMin = ImGui::GetWindowContentRegionMin();
            ImVec2 windowContentRegionMax = ImGui::GetWindowContentRegionMax();

            windowContentRegionSize.x = windowContentRegionMax.x - windowContentRegionMin.x;
            windowContentRegionSize.y = windowContentRegionMax.y - windowContentRegionMin.y;
        }

        ImVec2 toolbarSize = toolbarCursorEnd;
        toolbarSize.x -= toolbarCursorStart.x;
        toolbarSize.y -= toolbarCursorStart.y;



        ImVec2 inputTextSize = windowContentRegionSize;
        inputTextSize.x -= toolbarSize.x;
        inputTextSize.y -= toolbarSize.y;
        //ImGui::InputTextMultiline(ImGuiItem::AppendIdentifier("##InputText").c_str(), &mText, inputTextSize);
        mTextEditor.Render(ImGuiItem::AppendIdentifier("##InputText").c_str());
    }
}