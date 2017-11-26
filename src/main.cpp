#include <QtCore>
#ifdef Q_OS_WIN32
#include <Windows.h>
#endif
#include "DI.hpp"
#include <MellowPlayer/Infrastructure/Applications/DeprecatedSingleInstanceApplication.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/CommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/DeprecatedApplicationViewModel.hpp>
#include <MellowPlayer/Domain/BuildConfig.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>

namespace di = boost::di;
using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

int main(int argc, char** argv)
{
    // Init resources embedded in static libraries
    Q_INIT_RESOURCE(domain);
    Q_INIT_RESOURCE(presentation);
    qputenv("QTWEBENGINE_DIALOG_SET", "QtQuickControls2");
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "4242");

    // commented on purpose, see github issue #71
    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    DeprecatedApplicationViewModel qtApp(argc, argv);

    CommandLineArguments commandLineParser;
    commandLineParser.parse();
    qtApp.setAutoQuitDelay(commandLineParser.autoQuitDelay());

    unique_ptr<ILoggerFactory> loggerFactory = make_unique<SpdLoggerFactory>();
    LoggingManager::initialize(loggerFactory, commandLineParser.logLevel());
    ScopedScope scope{};
    LOG_INFO(LoggingManager::logger("main"), "Log directory: " + FileHelper::logDirectory());
    LOG_INFO(LoggingManager::logger("main"), QString("MellowPlayer %1 - %2").arg(QString(BuildConfig::getVersion())).arg(qtApp.buildInfo()));

    qtApp.initialize();

    auto injector = di::make_injector(di::bind<IDeprecatedQtApplication>().to(qtApp), di::bind<ICommandLineArguments>().to(commandLineParser),
                                      defaultInjector(scope), platformInjector(scope), notificationPresenterInjector(scope));

#ifdef QT_DEBUG
    IDeprecatedApplication& app = injector.create<IDeprecatedApplication&>();
    app.initialize();
#else
    DeprecatedSingleInstanceApplication& app = injector.create<DeprecatedSingleInstanceApplication&>();
#endif
    auto retCode = app.run();

    if (qtApp.restartRequested())
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

    return retCode;
}
