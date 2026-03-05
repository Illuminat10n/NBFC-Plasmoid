#pragma once

#include <QAbstractListModel>
#include "fan.h"

#include <qqmlregistration.h>

#undef QT_NO_CAST_FROM_ASCII
#undef QT_RESTRICTED_CAST_FROM_ASCII
#undef QT_NO_CAST_TO_ASCII

class FanModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT
public:

    Q_INVOKABLE void refresh();

    enum FanRoles {
        NameRole = Qt::UserRole + 1,
        CurrentSpeedRole = Qt::UserRole + 2,
        TargetSpeedRole = Qt::UserRole + 3
    };
    Q_ENUM(FanRoles)

    FanModel(QObject* parent = nullptr);
    ~FanModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    void addFan(Fan* fan);

private:
    QList<Fan*> m_fans;
    QList<Fan*> nbfc_exe_fan_init();

};
