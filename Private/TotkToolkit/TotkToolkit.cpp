#include <TotkToolkit/TotkToolkit.h>


#include <iostream>
#ifdef SWITCH
#include <switch.h>
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_opengl3.cpp> // Include this here so it uses our OpenGL loader (GLAD)
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_glfw.cpp> // Same with this one

#include <TotkToolkit/UI/MainWindow.h>
#include <TotkToolkit/UI/Windows/Rendering/Viewport.h>
#include <TotkToolkit/Rendering/RenderingSystem.h>

int main()
{
#if (SWITCH)
    romfsInit();
#endif

	if (!glfwInit())
		return 0;
    #if (SWITCH)
	    GLFWwindow* window = glfwCreateWindow(640, 480, "TotkToolkit", glfwGetPrimaryMonitor(), NULL);
    #else
        GLFWwindow* window = glfwCreateWindow(640, 480, "TotkToolkit", NULL, NULL);
    #endif

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigInputTrickleEventQueue = false;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    #if (!SWITCH)
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    #endif
    #if (SWITCH)
        io.AddMouseSourceEvent(ImGuiMouseSource_TouchScreen);
    #endif

    // Setup Dear ImGui style
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.80f, 0.83f, 0.96f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.18f, 0.21f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.16f, 0.18f, 0.21f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.21f, 0.25f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.13f, 0.14f, 0.16f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.40f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.18f, 0.21f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.15f, 0.18f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.18f, 0.21f, 0.94f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.37f, 0.53f, 0.71f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.24f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.53f, 0.54f, 0.54f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.32f, 0.34f, 0.38f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.82f, 0.82f, 0.82f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.53f, 0.53f, 0.53f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.12f, 0.15f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.19f, 0.19f, 0.22f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.16f, 0.18f, 0.21f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.13f, 0.14f, 0.98f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.18f, 0.21f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.12f, 0.12f, 0.14f, 0.70f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.45f, 0.68f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.66f, 1.00f, 0.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    ImGui::GetStyle().FrameRounding = 3;

    // Load fonts
#if (SWITCH)
    ImGui::GetIO().Fonts->AddFontFromFileTTF("romfs:/Resources/Fonts/Roboto.ttf", 24.f);
#else
    ImGui::GetIO().Fonts->AddFontFromFileTTF("Resources/Fonts/Roboto.ttf", 16.f);
#endif

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImVec4 clearColor = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
    bool showDemoWindow = true;

    TotkToolkit::Rendering::RenderingSystem::Init();

    TotkToolkit::UI::MainWindow mainWindow;

    TotkToolkit::UI::Windows::Rendering::Viewport viewport("Viewport");

	while (!glfwWindowShouldClose(window))
	{
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);
        
        mainWindow.Draw();
        viewport.Draw();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) 
        { 
            GLFWwindow* backup_current_context = glfwGetCurrentContext(); 
            ImGui::UpdatePlatformWindows(); 
            ImGui::RenderPlatformWindowsDefault(); 
            glfwMakeContextCurrent(backup_current_context); 
        } 

    	glfwSwapBuffers(window);
	}

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	glfwDestroyWindow(window);
    
    glfwTerminate();
	
	return 0;
}
