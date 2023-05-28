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
#include <TotkToolkit/UI/Windows/Editors/Text.h>

int main()
{
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
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImVec4 clearColor = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
    bool showDemoWindow = true;
    TotkToolkit::UI::MainWindow mainWindow;
    TotkToolkit::UI::Windows::Editors::Text sdf("Text editor");

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
        sdf.Draw();

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
