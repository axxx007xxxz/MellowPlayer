#pragma once

#include <MellowPlayer/Application/Logging/ILogger.hpp>

namespace spdlog {
class logger;
}

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SpdLogger: public Application::ILogger {
public:
    SpdLogger(const std::string& name, const Application::LoggerConfig& config);
    ~SpdLogger();
    void log(const std::string &message, Application::LogLevel level, const char* file, int line) override;
    const std::string& getName() const override;

private:
    std::shared_ptr<spdlog::logger> logger;
    bool includeFileAndLine;
    std::string name;
};

END_MELLOWPLAYER_NAMESPACE