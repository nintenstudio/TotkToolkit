#pragma once

#include <TotkToolkit/Messaging/ExternalReceivers/UI/ErrorSystem.h>
#include <string>
#include <vector>
#include <shared_mutex>

namespace TotkToolkit::UI {
    class ErrorSystem {
    public:
        static void Init();

        static void Draw();

    protected:
        friend class TotkToolkit::Messaging::ExternalReceivers::UI::ErrorSystem;

        static std::vector<std::string> sMessages; static std::shared_mutex sMessagesMutex;
        static TotkToolkit::Messaging::ExternalReceivers::UI::ErrorSystem sExternalReceiver;
    };
}