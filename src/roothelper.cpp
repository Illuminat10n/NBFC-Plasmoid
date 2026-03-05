#include "roothelper.h"

ActionReply RootHelper::setfanspeed(const QVariantMap& args)
{
    QProcess process;

    process.setProgram(QString::fromUtf8("nbfc"));

    QStringList arguments;

    if (args[QString::fromUtf8("speed")].toInt() < 35){
        arguments << QString::fromUtf8("set") << QString::fromUtf8("-a") << QString::fromUtf8("-f") << args[QString::fromUtf8("fan")].toString() ;
    }
    else {
        arguments << QString::fromUtf8("set") << QString::fromUtf8("-s") << args[QString::fromUtf8("speed")].toString() << QString::fromUtf8("-f") << args[QString::fromUtf8("fan")].toString() ;
    }

    process.setArguments(arguments);
    process.startDetached();

    process.waitForFinished(-1);

    if (!process.waitForStarted() || !process.waitForFinished()) {
        qDebug() << "Error executing command:" << process.errorString();
        return 1;
    }

    qDebug() << "Command executed successfully";
    return 0;

}

KAUTH_HELPER_MAIN("org.kde.plasma.omenctlnew", RootHelper)
