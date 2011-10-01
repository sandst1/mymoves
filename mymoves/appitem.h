#ifndef APPITEM_H
#define APPITEM_H

#include <QByteArray>
#include <QHash>
#include <QObject>
#include <QString>
#include <QVariant>

#include <QDebug>
#include "listmodel.h"
//#include "app.h"

class AppItem : public ListItem
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole+1
        ,CommandRole
        ,IconRole
    };

    AppItem(QObject* parent = 0): ListItem(parent) {}
    explicit AppItem(const QString& name, const QString& command, const QString& icon, QObject *parent = 0);
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    inline QString id() const { return m_name; }

    inline QString name() const { return m_name; }
    inline QString command() const { return m_command; }
    inline QString icon() const { return m_icon; }
signals:
    void dataChanged();
public slots:

private:
    QString m_name;
    QString m_command;
    QString m_icon;
};

#endif // APPITEM_H
