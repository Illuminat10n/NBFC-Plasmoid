/*
    SPDX-FileCopyrightText: 2022 illusion <vladmak04@gmail.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "roothelper.h"
#include "fan.h"
#include "fanmodel.h"

#pragma once
#include <Plasma/plasma_version.h>
#include <Plasma/plasma/plasma_export.h>


#include "KF6/KConfig/kconfig_version.h"
#include <KF6/KConfigCore/kconfigcore_export.h>

#include <KF6/KConfigCore/kconfig.h>
#include <KF6/KConfigCore/kconfiggroup.h>


#include <Plasma/plasma/applet.h>
#include <KLocalizedString>

#include <QQmlDebuggingEnabler>

//Who the fuck thought it was a good idea????
#undef QT_NO_CAST_FROM_ASCII
#undef QT_RESTRICTED_CAST_FROM_ASCII
#undef QT_NO_CAST_TO_ASCII

class OmenCtl : public Plasma::Applet {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int cpuCool READ getCpuCool WRITE setCpuCool)
    Q_PROPERTY(int gpuCool READ getGpuCool WRITE setGpuCool)
    Q_PROPERTY(QVariant fanModel READ fanModel CONSTANT)

public:
    OmenCtl( QObject *parent, const KPluginMetaData &data, const QVariantList &args );
    ~OmenCtl();

    QVariant fanModel() const;
    void setCpuCool(short n);
    int getCpuCool() const;

    void setGpuCool(short n);
    int getGpuCool() const;

    Q_INVOKABLE void setFanSpeed(unsigned short fan, unsigned short speed);
    FanModel* m_fanModel = nullptr;

private:

    int cpuCool = 30;
    int gpuCool;
};
