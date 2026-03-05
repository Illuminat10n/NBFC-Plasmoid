#include "fan.h"

#include <kauth/action.h>
#include <kauth/executejob.h>


Fan::Fan(QString name, double current, double target, bool autoControl, int number, QObject *parent) : QObject(parent),
    m_name(name), m_currentSpeed(current), m_targetSpeed(target), m_number(number), m_autoControl(autoControl)
{

}


void Fan::setTargetSpeed(double target){
    KAuth::Action set_fan_action(QString::fromUtf8("org.kde.plasma.omenctlnew.setfanspeed"));
    set_fan_action.setHelperId(QString::fromUtf8("org.kde.plasma.omenctlnew"));

    QVariantMap map;
    map[QString::fromUtf8("fan")] = number();
    map[QString::fromUtf8("speed")] = (int) target;
    set_fan_action.setArguments(map);
    KAuth::ExecuteJob* job = set_fan_action.execute();
    if (!job->exec()) {
        qDebug() << "KAuth returned an error code:" << job->error() << '\n';
        qDebug() << job->errorString();
    } else {
        qDebug() << "KAuth succeeded." ;
    }
}

int Fan::number() const
{
    return m_number;
}

QString Fan::name() const { return m_name; }
double Fan::currentSpeed() const { return m_currentSpeed; }
double Fan::targetSpeed() const {return m_targetSpeed; }
bool Fan::autoControl() const {return m_autoControl; }
