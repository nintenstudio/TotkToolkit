add_library(ImGuiColorTextEdit STATIC 
Lib/ImGuiColorTextEdit/TextEditor.h 
Lib/ImGuiColorTextEdit/TextEditor.cpp
Lib/ImGuiColorTextEdit/LanguageDefinitions.cpp
)

target_include_directories(ImGuiColorTextEdit PRIVATE Lib/ImGuiColorTextEdit)

set(BOOST_REGEX_STANDALONE true CACHE BOOL "" FORCE)
add_subdirectory(Lib/ImGuiColorTextEdit/vendor/regex)
target_link_libraries(ImGuiColorTextEdit PUBLIC boost_regex)

target_include_directories(ImGuiColorTextEdit PUBLIC Lib/ImGui)