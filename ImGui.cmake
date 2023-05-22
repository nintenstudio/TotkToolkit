add_library(ImGui STATIC 
Lib/ImGui/imgui.h 
Lib/ImGui/imgui.cpp 
Lib/ImGui/imstb_rectpack.h 
Lib/ImGui/imstb_textedit.h 
Lib/ImGui/imstb_truetype.h 
Lib/ImGui/imgui_demo.cpp 
Lib/ImGui/imgui_draw.cpp 
Lib/ImGui/imgui_internal.h 
Lib/ImGui/imgui_tables.cpp 
Lib/ImGui/imgui_widgets.cpp 
Lib/ImGui/backends/imgui_impl_opengl3.h 
#Lib/ImGui/backends/imgui_impl_opengl3.cpp # Instead we include this from our code so that it uses our opengl loader (GLAD)
Lib/ImGui/backends/imgui_impl_glfw.h 
#Lib/ImGui/backends/imgui_impl_glfw.cpp # Same with this one
)

target_include_directories(ImGui PRIVATE Lib/ImGui)