#include <TotkToolkit/Rendering/DebugMessageHandler.h>

#include <glad/glad.h>
#include <iostream>

void GLAPIENTRY
DebugMessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    if (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_HIGH) {
        std::fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
    }
}

namespace TotkToolkit::Rendering {
	void DebugMessageHandler::Init() {
#ifndef NDEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(DebugMessageCallback, 0);
#endif
	}
}