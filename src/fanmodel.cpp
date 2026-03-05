#include "fanmodel.h"

#include <QProcess>
#include <QStringList>
#include <QRegularExpression>
#include <QDebug>
#include <QVariant>

#undef QT_NO_CAST_FROM_ASCII
#undef QT_RESTRICTED_CAST_FROM_ASCII
#undef QT_NO_CAST_TO_ASCII

void FanModel::refresh()
{
    beginResetModel();
    m_fans.clear();
    m_fans = nbfc_exe_fan_init();
    endResetModel();
    qDebug() << "Model reset";
}

FanModel::FanModel(QObject* parent) : QAbstractListModel(parent) {
    m_fans = nbfc_exe_fan_init();
    qDebug() << QString::fromLatin1("Model created!");
}

FanModel::~FanModel()
{
    qDebug() << QString::fromLatin1("Model destroyed!");
    QAbstractListModel::~QAbstractListModel();
}

int FanModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    //qDebug() << QString::fromLatin1("Called Size: ") + QString::number(m_fans.size());
    return m_fans.size();
}

QVariant FanModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_fans.size()) {
        return QVariant();
    }

    Fan* fan = m_fans[index.row()];

    if (role == NameRole || role == Qt::DisplayRole){
        //qDebug() << QString::fromLatin1("Called Name") + fan->name();
        return fan->name();
    }
    else if (role == CurrentSpeedRole){
        //qDebug() << QString::fromLatin1("Called Current Speed") + QString::number(fan->currentSpeed());
        return fan->currentSpeed();
    }
    else if (role == TargetSpeedRole){
        //qDebug() << QString::fromLatin1("Called Target Speed") + QString::number(fan->targetSpeed());
        return fan->targetSpeed();
    }

    return QVariant();
}

bool FanModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || index.row() >= m_fans.size())
        return false;

    Fan* fan = m_fans[index.row()];
    if (role == TargetSpeedRole) {
        fan->setTargetSpeed(value.toInt());
        Q_EMIT dataChanged(index, index, { TargetSpeedRole });
        return true;
    }

    return false;
}

QHash<int, QByteArray> FanModel::roleNames() const {
    QHash<int, QByteArray> roles = {
    {Qt::DisplayRole, QByteArrayLiteral("display")},
    {Qt::DecorationRole, QByteArrayLiteral("decoration")},
    {NameRole, QByteArrayLiteral("name")},
    {CurrentSpeedRole, QByteArrayLiteral("currentSpeed")},
    {TargetSpeedRole, QByteArrayLiteral("targetSpeed")}
    };

    return roles;
}

void FanModel::addFan(Fan* fan) {
    beginInsertRows(QModelIndex(), m_fans.size(), m_fans.size());
    m_fans.append(fan);
    endInsertRows();
}

QList<Fan *> FanModel::nbfc_exe_fan_init()
{
    QProcess proc;
    proc.start(QString::fromStdString("nbfc"),
               {QString::fromStdString("status"), QString::fromStdString("-a")});
    proc.waitForFinished();

    QString output = QString::fromStdString(proc.readAllStandardOutput().toStdString());
    qDebug() << output;
    QStringList lines = output.split(QString::fromStdString("\n"));

    QList<Fan*> fans = QList<Fan*>();
    QString name;
    int number = 0;
    double currentSpeed = -1;
    double targetSpeed = -1;
    bool autoControl = false;

    for (const QString &line : lines) {
        if (line.startsWith(QStringLiteral("Fan display name"))) {
            name = line.section(QLatin1Char(':'), 1).trimmed();
        } else if (line.startsWith(QStringLiteral("Auto control enabled"))) {
            autoControl = line.section(QLatin1Char(':'), 1).trimmed().toLower() == QStringLiteral("true");
        }
        else if (line.startsWith(QStringLiteral("Current fan speed"))) {
            currentSpeed = line.section(QLatin1Char(':'), 1).trimmed().toDouble();
        } else if (line.startsWith(QStringLiteral("Target fan speed"))) {
            targetSpeed = line.section(QLatin1Char(':'), 1).trimmed().toDouble();
            if (!name.isEmpty() && currentSpeed > -1 && targetSpeed > -1) {
                fans.append(new Fan(name, currentSpeed, targetSpeed, autoControl, number, NULL));
                name.clear();
                number++;
                currentSpeed = -1;
                targetSpeed = -1;
                autoControl = false;
            }
        }
    }

    return fans;
}

#include "moc_fanmodel.cpp"
