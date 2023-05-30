#include <TotkToolkit/UI/ImGuiItem.h>

#include <Formats/Aliases/Primitives.h>

namespace TotkToolkit::UI {
    std::string ImGuiItem::AppendIdentifier(std::string text) {
        return text + "##" + mId;
    }

    F_UINT ImGuiItem::mIdCounter = 0;
}