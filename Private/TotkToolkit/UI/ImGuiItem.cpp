#include <TotkToolkit/UI/ImGuiItem.h>

#include <Formats/Aliases/Primitives.h>

namespace TotkToolkit::UI {
    std::string ImGuiItem::AppendIdentifier(std::string text, std::string additionalIdentification) {
        return text + "##" + additionalIdentification + mId;
    }
    std::string ImGuiItem::AppendExclusiveIdentifier(std::string text, std::string additionalIdentification) {
        return text + "###" + additionalIdentification + mId;
    }
    std::string ImGuiItem::GetIdentifier() {
        return mId;
    }

    F_U32 ImGuiItem::mIdCounter = 0;
}