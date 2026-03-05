/*
    SPDX-FileCopyrightText: 2023 illusion <vladmak04@gmail.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "omenctl.h"
#include <QQmlEngine>


OmenCtl::OmenCtl(QObject *parent, const KPluginMetaData &data, const QVariantList &args) : Plasma::Applet(parent, data, args)
{
    QQmlDebuggingEnabler::enableDebugging(true);
    qmlRegisterType<FanModel>("OmenCtl", 1, 0, "FanModel");
    m_fanModel = new FanModel(this);
}

OmenCtl::~OmenCtl()
{
}

QVariant OmenCtl::fanModel() const
{
    return QVariant::fromValue(m_fanModel);
}

int OmenCtl::getCpuCool() const
{
    return cpuCool;
}

int OmenCtl::getGpuCool() const
{
    return gpuCool;
}

void OmenCtl::setFanSpeed(unsigned short fan, unsigned short speed)
{
    KAuth::Action set_fan_action(QString::fromUtf8("org.kde.plasma.omenctlnew.setfanspeed"));
    set_fan_action.setHelperId(QString::fromUtf8("org.kde.plasma.omenctlnew"));

    QVariantMap map;
    map[QString::fromUtf8("fan")] = fan;
    map[QString::fromUtf8("speed")] = speed;
    set_fan_action.setArguments(map);
    ExecuteJob* job = set_fan_action.execute();
    if (!job->exec()) {
        qDebug() << "KAuth returned an error code:" << job->error() << '\n';
        qDebug() << job->errorString();
    } else {
        qDebug() << "KAuth succeeded." ;
    }
}

void OmenCtl::setCpuCool(short n)
{
    setFanSpeed(0, n);
}

void OmenCtl::setGpuCool(short n)
{
    setFanSpeed(1, n);
}

K_PLUGIN_CLASS_WITH_JSON(OmenCtl, "package/metadata.json")

#include "omenctl.moc"
