#include <TotkToolkit/UI/ImGuiItem.h>

#include <Formats/Aliases/Primitives.h>

namespace TotkToolkit::UI {
    std::string ImGuiItem::AppendIdentifier(std::string text) {
        return text + "##" + mId;
    }

    UINT ImGuiItem::mIdCounter = 0;
}