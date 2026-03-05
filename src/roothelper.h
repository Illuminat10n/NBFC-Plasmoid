#include <KAuth/ActionReply>
#include <KAuth/ExecuteJob>
#include <KAuth/HelperSupport>


#include <QProcess>
#include <QDebug>
#include <QVariantMap>

using namespace KAuth;

class RootHelper : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    ActionReply setfanspeed(const QVariantMap& args);
    //ActionReply setfanautocontrol(const QVariantMap& args);
};
