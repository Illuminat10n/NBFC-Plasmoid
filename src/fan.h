// fan.h
#pragma once
#include <QObject>

class Fan : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(double currentSpeed READ currentSpeed NOTIFY currentSpeedChanged)
    Q_PROPERTY(double targetSpeed READ targetSpeed WRITE setTargetSpeed NOTIFY targetSpeedChanged)
    Q_PROPERTY(bool autoControl READ autoControl NOTIFY autoControlChanged)
    Q_PROPERTY(int number READ number CONSTANT)

public:
    Fan(QString name, double current, double target, bool autoControl, int number, QObject *parent = nullptr);

    QString name() const;
    double currentSpeed() const;
    double targetSpeed() const;
    void setTargetSpeed(double speed);
    int number() const;
    bool autoControl() const;

Q_SIGNALS:
    void currentSpeedChanged();
    void targetSpeedChanged();
    void autoControlChanged();

private:
    QString m_name;
    int m_number;
    double m_currentSpeed;
    double m_targetSpeed;
    bool m_autoControl;
};
