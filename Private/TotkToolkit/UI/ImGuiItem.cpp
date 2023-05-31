#include <TotkToolkit/UI/ImGuiItem.h>

#include <Formats/Aliases/Primitives.h>

namespace TotkToolkit::UI {
    std::string ImGuiItem::AppendIdentifier(std::string text) {
        return text + "##" + mId;
    }

    F_U32 ImGuiItem::mIdCounter = 0;
}