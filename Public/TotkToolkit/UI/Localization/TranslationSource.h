#pragma once

#include <string>

namespace TotkToolkit::UI::Localization {
    class TranslationSource {
    public:
        static std::string GetText(std::string internal) {
            // TOTKTOOLKIT_TODO_FUNCTIONAL: Implement languages resource.
            return internal;
        }
        static char* GetText(char* internal)  {
            // TOTKTOOLKIT_TODO_FUNCTIONAL: Implement languages resource.
            return internal;
        }
        static char* GetText(const char* internal)  {
            // TOTKTOOLKIT_TODO_FUNCTIONAL: Implement languages resource.
            return (char*)internal;
        }
    };
}