#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceLoader.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_STRUCT(Application, StreamingServiceMetadata)
PREDECLARE_MELLOWPLAYER_STRUCT(Application, StreamingServiceStyle)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class StreamingServiceLoader: public Application::IStreamingServiceLoader {
public:
    StreamingServiceLoader();
    QList<std::shared_ptr<Application::StreamingService>> load() const override;

private:
    std::unique_ptr<Application::StreamingService> loadPlugin(const QString &directory) const;
    QString findFileByExtension(const QString &directory, const QString &suffix) const;
    QString readFileContent(const QString &filePath) const;
    Application::StreamingServiceMetadata readMetadata(const QString &filePath) const;
    Application::StreamingServiceStyle readStyle(const QString &filePath) const;
    bool checkPluginDirectory(const QString &directory) const;
    QString getUserPluginsDirectory() const;
    QStringList getSearchPaths() const;
    bool containsPlugin(const QList<std::shared_ptr<Application::StreamingService>> &plugins,
                        std::shared_ptr<Application::StreamingService>& toCheck) const;

    Application::ILogger& logger;
};

END_MELLOWPLAYER_NAMESPACE