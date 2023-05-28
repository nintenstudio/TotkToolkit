#pragma once

#include <Formats/Aliases/Primitives.h>

#include <string>
#include <iomanip>

namespace TotkToolkit::UI {
    class ImGuiItem {
public:
        ImGuiItem() {
            std::stringstream counterFormatStream;
            counterFormatStream << std::hex << mIdCounter;
            mId = counterFormatStream.str();
            mIdCounter++;
        }

        virtual void Draw() = 0;
protected:
        std::string AppendIdentifier(std::string text);

        std::string mId; // ImGui requires unique names for a lot of items it renders. It does, luckily, allow you to append an invisible string at the end of the name for ID purposes. This is something that can be included to differentiate elements from different windows.
    
private:
        static UINT mIdCounter;
    };
}