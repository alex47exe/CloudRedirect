#pragma once
#include "common.h"
#include <string>

namespace Log {
    void Init(const char* path);
    void Shutdown();
    void Write(const char* fmt, ...);

    // Per-app log context: while set on this thread, Write() also appends to
    // the app's own cloud_redirect.log inside its storage folder.
    void SetAppContext(const std::string& appLogPath);
    void ClearAppContext();

    struct AppScope {
        explicit AppScope(const std::string& appLogPath) {
            if (!appLogPath.empty()) SetAppContext(appLogPath);
        }
        ~AppScope() { ClearAppContext(); }
        AppScope(const AppScope&) = delete;
        AppScope& operator=(const AppScope&) = delete;
    };
}

#define LOG(fmt, ...) Log::Write(fmt, ##__VA_ARGS__)
