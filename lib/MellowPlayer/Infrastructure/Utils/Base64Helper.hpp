#pragma once

#include <QtGui/QImage>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Base64Helper: public QObject {
    Q_OBJECT
public:
    Base64Helper(QObject* parent=nullptr);

    Q_INVOKABLE bool isBase64(const QString& uri);
    Q_INVOKABLE QImage getImage(const QString& uri);
    Q_INVOKABLE bool saveToFile(const QString& uri, const QString& path);
    Q_INVOKABLE QString getImageProviderUrl(const QString& url);

private:
    Application::ILogger& logger;

};

END_MELLOWPLAYER_NAMESPACE