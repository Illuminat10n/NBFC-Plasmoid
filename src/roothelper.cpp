#include "roothelper.h"

ActionReply RootHelper::setfanspeed(const QVariantMap& args)
{
    auto *process = new QProcess(this);
    process->setProgram(QString::fromUtf8("nbfc"));

    QStringList arguments;

    if (args[QString::fromUtf8("speed")].toInt() < 35){
        arguments << QString::fromUtf8("set") << QString::fromUtf8("-a") << QString::fromUtf8("-f") << args[QString::fromUtf8("fan")].toString() ;
    }
    else {
        arguments << QString::fromUtf8("set") << QString::fromUtf8("-s") << args[QString::fromUtf8("speed")].toString() << QString::fromUtf8("-f") << args[QString::fromUtf8("fan")].toString() ;
    }

    process->setArguments(arguments);

    connect(process, &QProcess::finished,
            this,
            [process](int exitCode, QProcess::ExitStatus status)
            {
                process->deleteLater();
            });

    process->start();

    return ActionReply::SuccessReply();
}

KAUTH_HELPER_MAIN("org.kde.plasma.omenctlnew", RootHelper)
